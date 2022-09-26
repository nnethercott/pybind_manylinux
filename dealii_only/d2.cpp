#include "mpi.h"
#include <deal.II/base/index_set.h>
#include <deal.II/lac/trilinos_vector.h>
#include <iostream>


void vhello(const unsigned &block){
  using dealii::IndexSet, dealii::TrilinosWrappers::MPI::Vector;
  using std::cout, std::endl;

  MPI_Init(NULL, NULL);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  //add an interval in a localized way
  IndexSet parallel_partitioning(size*block);
  parallel_partitioning.add_range(rank*block, (rank+1)*block);

  //now write to vector
  Vector v(parallel_partitioning, MPI_COMM_WORLD);
  int base = rank*block;
  for (auto i : v.locally_owned_elements()){
    v[i] = base++;
  }

  MPI_Finalize();

  //print
  cout<<"rank: "<<rank<<", elements: ";
  for(auto it = v.begin(); it!=v.end(); it++){
    cout<<(*it)<<" ";
  }
  cout<<endl;
}

int main(){
  vhello(4);
}
