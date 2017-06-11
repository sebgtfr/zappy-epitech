//
// main.cpp for zappy in /home/le-mai_s/test/zappy
//
// Made by Sébastien Le Maire
// Login   <le-mai_s@epitech.net>
//
// Started on  Sun Jun 26 23:12:49 2016 Sébastien Le Maire
// Last update Sun Jun 26 23:22:14 2016 Sébastien Le Maire
//

#include <cstdlib>
#include <iostream>
#include "ClientTCP.hpp"

int		main(int ac, char **av)
{
  TCP::Client	client;

  if (ac == 3)
    {
      if (client.init(static_cast<uint16_t>(atoi(av[2])), av[1]))
	client.launch();
      else
	std::cerr << "Error: init client failed !" << std::endl;
    }
  else
    std::cerr << "Usage: " << av[0] << " [HOST] [PORT]" << std::endl;
  return (EXIT_SUCCESS);
}
