#include <stdlib.h>
#include <stdio.h>
#include <ctime>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "renderer.h"
#include "cuberobot.h"
#include "cubeobstacle.h"
#include "Graph.h"
#include "AStarPlanner.h"
#include "KNearest.h"
#include "StraightLinePlanner.h"
#include "UniformSampler.h"
#include "PRM.h"

// Interpolation between c1 and c2 and return the sequence of interpolation
RealCoordVector Interpolate(const RealCoord &c1, 
                            const RealCoord &c2, 
                            double res) {
  unsigned dim = c1.dim();
  assert(dim == c2.dim());
  RealCoordVector points;
  Euclidean dist;
  int step = (int)(dist(c1, c2) / res);
  if (step > 0) {
    RealCoord delta(dim);
    for (unsigned i = 0; i < dim; ++i) {
      delta[i] = (c2[i] - c1[i]) / step;
    }
    RealCoord current = c1;
    for (int i = 0; i < step; ++i) {
      current += delta;
      points.push_back(current);
    }
  }
  return points;
}
// Subdivide the path with a given resolution, return a "detailed" path.
RealCoordVector SubdividePath(const RealCoordVector &path, double res) {
  RealCoordVector subpath;
  if (!path.empty()) {
    for (RealCoordVector::const_iterator iter = path.begin(); 
        iter != path.end(); ++iter) {
      RealCoordVector::const_iterator next_iter = iter + 1;
	  if (next_iter != path.end()) {
        subpath.push_back(*iter);
        RealCoordVector points = Interpolate(*iter, *next_iter, res);
        subpath.insert(subpath.end(), points.begin(), points.end());
	  }
    }
    subpath.push_back(path.back());
  }
  return subpath;
}
// Print coordinate
void PrintCoord(const RealCoord &c) {
  unsigned dim = c.dim();
  for (unsigned i = 0; i < dim; ++i) {
	  std::cout << c[i] << ' ';
  }
  std::cout << std::endl;
}
static void error_callback(int error, const char* description) {
  fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, 
                         int key, int scancode, 
                         int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}
int main(void) {
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }
  window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);

  //Initialize one cube robot and three cube obstacles.
  Robot *rob = new CubeRobot();
  Obstacle *obs1 = new CubeObstacle();
  Obstacle *obs2 = new CubeObstacle();
  Obstacle *obs3 = new CubeObstacle();

  // Set obstacles' configuration .
  double ostate1[] = {-2.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double ostate2[] = {-2.0, 0.0, 3.0, 0.0, 0.0, 0.0};
  double ostate3[] = {-2.0, 0.0, -3.0, 0.0, 0.0, 0.0};
  Coordinate<double> obstacle_state1(ostate1, 6);
  Coordinate<double> obstacle_state2(ostate2, 6);
  Coordinate<double> obstacle_state3(ostate3, 6);
  obs1->set_state(obstacle_state1);
  obs2->set_state(obstacle_state2);
  obs3->set_state(obstacle_state3);

  // Set lower and upper state for the robot.
  double lower[] = {-8.0, -8.0, -8.0, 0.0, 0.0, 0.0};
  double upper[] = {8.0, 8.0, 8.0, 360.0, 360.0, 360.0};
  Coordinate<double> lower_bound(lower, 6);
  Coordinate<double> upper_bound(upper, 6);
  rob->set_lower_state(lower_bound);
  rob->set_upper_state(upper_bound);

  // Initialize the scene, add robot(s) and obstacle(s) into the scene.
  Scene scene;
  scene.AddRobot(rob);
  scene.AddObstacle(obs1);
  scene.AddObstacle(obs2);
  scene.AddObstacle(obs3);

  // Initialize PRM and its data member.
  ConfigurationSpace cspace(&scene);
  Euclidean metric;
  KNearest nn(5);
  Rng rng((unsigned)(std::time(NULL)));
  UniformSampler sp(&rng);
  StraightLinePlanner lp(5.0);  // Set the resolution to be 5.0
  AStarPlanner gp(&metric);  // Use a-star algorithm as the global planner
  PRM prm(&cspace, &metric, &sp, &nn, &lp, &gp);

  // Construct the roadmap. To such a simple planning task, 
  // 500 samples is enough.
  prm.ConstructRoadmap(500);

  // Set the start and goal configuration.
  double start[] = {2.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double goal[] = {-6.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Coordinate<double> start_state(start, 6);
  Coordinate<double> goal_state(goal, 6);

  // Query a collision-free path.
  IntVector path = prm.SolveQuery(start_state, goal_state);

  PlanningGraph graph = prm.roadmap();
  //std::cout << "number of vertices: " << graph.num_vertices() << ' ' 
  //<< "number of edges: " << graph.num_edges() << std::endl;
  std::vector<Vertex*> vertices = graph.vertices();
  //std::cout << "path size: " << path.size() << std::endl;

  // Get coordinates of vertices in the path.
  RealCoordVector milestones;
  if (!path.empty()) {
    for (IntVector::size_type i = 1; i < path.size() - 1; ++i) {
      Coordinate<double> state = static_cast<PlanningVertex*>(vertices[i])->state();
      milestones.push_back(state);
    }
  }
  milestones.insert(milestones.begin(), start_state);
  milestones.push_back(goal_state);

  // Initialize the renderer.
  Renderer renderer;
  renderer.LoadShader("shader/transform_vertex_shader.vertexshader", 
                      "shader/texture_fragment_shader.fragmentshader");
  renderer.LocateMVPMatrix("MVP");
  renderer.set_view_matrix(Vec3(20, 3, 0), Vec3(0, 0, 0), Vec3(0, 1, 0));
  renderer.AddRenderObject(rob);
  renderer.AddRenderObject(obs1);
  renderer.AddRenderObject(obs2);
  renderer.AddRenderObject(obs3);

  // Subdivide the path into subpath in order to implement animation.
  RealCoordVector subpath = SubdividePath(milestones, 5.0);
  //std::cout << "subpath size: " << subpath.size() << std::endl;

  RealCoordVector::size_type size = subpath.size();
  RealCoordVector::size_type i = 0;

  // Set states of all robots according to the start configuration.
  scene.Configuration2World(subpath[i]);
  renderer.UpdateMVP();

  double last_time = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    renderer.Render();
    double current_time = glfwGetTime();
    if (current_time - last_time > 0.1) {
      if (i >= size) continue;
        scene.Configuration2World(subpath[i]);
        renderer.UpdateMVP();
        last_time = current_time;
        ++i;
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  delete rob;
  delete obs1;
  delete obs2;
  delete obs3;
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}