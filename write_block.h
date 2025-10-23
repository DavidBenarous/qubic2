#ifndef _WRITE_BLOCK_H
#define _WRITE_BLOCK_H

#include "struct.h"
#include <memory>
#include <iostream>

template <typename Block>
void print_bc(std::ostream &fw, const std::unique_ptr<Block> &b, int num);

#endif
