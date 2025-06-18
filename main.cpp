#include "includes/Includes.h"
#include <cstdlib>

int main(int ac, char **av) {
  (void)ac;
  if (ac != 4)
    return 0;

  App app = App(atoi(av[1]), atoi(av[2]), av[3]);
  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// TODO - Manage Resize
// TODO - Clean properly
// TODO - Add .obj parsing
// TODO - Add movable camera
// TODO - ...lights?
