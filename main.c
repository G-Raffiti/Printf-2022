//
// Created by rbonneva on 10/12/23.
//
#include <stdio.h>
#include "ft_printf.h"

int main(int ac, char **av)
{
    (void)ac;
    dprintf(1, "%d\n", printf("%i %u %x %% %X\n", 785542, 85, 4654, 8732213));
    dprintf(1, "\n");
    dprintf(1, "%d\n", ft_printf("%i %u %x %% %X\n", 785542, 85, 4654, 8732213));
}