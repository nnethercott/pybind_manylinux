#include <pybind11/pybind11.h>

//new
/*
#include "mpi.h"
#include <deal.II/base/index_set.h>
#include <deal.II/lac/trilinos_vector.h>
#include <iostream>
*/

//new comment
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


int add(int i, int j) {
    return i + j;
}

/*
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
*/

namespace py = pybind11;

PYBIND11_MODULE(nate, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: python_example
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers
        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");


/*
    //new
    m.def("vhello", &vhello, R"pbdoc(
        a new function i've added to the module which uses dealii objects.
    )pbdoc");
*/

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
