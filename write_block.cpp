/******************************************************************/
/* Author: Qin Ma <maqin@uga.edu>, Step. 19, 2013
 * Output the identified bicluster block.
 */

#include "write_block.h"
#include <iomanip>

/*************************************************************************/

/* Identified clusters are backtraced to the original data, by
 * putting the clustered vectors together, identify common column
 */
template <typename Block>
void print_bc(std::ostream &fw, const std::unique_ptr<Block> &b, const int num) {
  /* block height (genes) */
  const int block_rows = b->genes.size();
  /* block_width (conditions) */
  const int block_cols = b->conds.size();
  
  const int core_rows = b->core_rownum;  /* core height*/
  const int core_cols = b->core_colnum;  /* core width*/
  fw << "BC" << std::setfill('0') << std::setw(3) << num << "\tS=" << block_rows * block_cols
     << "\tEnrichment:" << std::fixed << std::setprecision(2) << b->score / 100.0
     << "\tRow=" << block_rows << "\tCol=" << block_cols
     << "\tCore_Row=" << core_rows << "\tCore_Col=" << core_cols << "\t\n";

  fw << " Genes [" << block_rows << "]: ";
  for (auto gene : b->genes)
    fw << genes_n[gene] << " ";
  fw << "\n";

  fw << " Conds [" << block_cols << "]: ";
  for (auto cond : b->conds)
    fw << conds_n[cond] << " ";
  fw << "\n";
  /* the complete block data output */
  int i = 0;
  for (auto gene : b->genes) {
    fw << std::setw(10) << genes_n[gene] << ":";
    for (auto cond : b->conds) {
      fw << "\t" << symbols[arr_c[gene][cond]];
    }
    fw << '\n';
    if (i == b->block_rows_pre - 1)
      fw << '\n';
    i++;
  }
}

template void print_bc<Block>(std::ostream &fw, const std::unique_ptr<Block> &b,
                              int num);
template void print_bc<Block1>(std::ostream &fw, const std::unique_ptr<Block1> &b,
                               int num);
