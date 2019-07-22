#ifndef STAN_MATH_TORSTEN_MPI_COMMUNICATOR_HPP
#define STAN_MATH_TORSTEN_MPI_COMMUNICATOR_HPP

#ifdef TORSTEN_MPI

#include <stan/math/torsten/mpi/envionment.hpp>

namespace torsten {
  namespace mpi {
    /*
     * MPI communicator wrapper for RAII. Note that no
     * MPI's predfined comm sich as @c MPI_COMM_WOLRD are allowed.
     */
    struct Communicator {
    private:
      /*
       * Disable default constructor.
       */
      Communicator();

      const Envionment& env_;

    public:
      MPI_Comm comm;
      int size;
      int rank;

      /*
       * communicator constructor using @c Envionment and @c MPI_Comm
       */
      Communicator(const Envionment& env, MPI_Comm other) :
        env_(env), comm(MPI_COMM_NULL) {
        MPI_Comm_dup(other, &comm);
        MPI_Comm_size(comm, &size);
        MPI_Comm_rank(comm, &rank);        
      }

      /*
       * copy constructor is deep
       */
      explicit Communicator(const torsten::mpi::Communicator& other) :
        Communicator(other.env_, other.comm)
      {}

      /*
       * type-cast to MPI_Comm object
       */
      operator MPI_Comm() {
        return this -> comm;
      }

      /*
       * destructor needs to free MPI_Comm
       */
      ~Communicator() {
        MPI_Comm_free(&comm);
      }
    };

    /*
     * MPI communicator wrapper for RAII. Note that no
     * MPI's predfined comm sich as @c MPI_COMM_WOLRD are allowed.
     */
    // struct CommunicatorWithEnvionment : public Communicator {
    // private:
    //   const Envionment& env_;

    //   /*
    //    * Disable default constructor.
    //    */
    //   CommunicatorWithEnvionment();

    // public:
    //   CommunicatorWithEnvionment(const Envionment& env, MPI_Comm other) :
    //     Communicator(other),
    //     env_(env)
    //   {}

    //   /*
    //    * copy constructor is deep
    //    */
    //   explicit CommunicatorWithEnvionment(const torsten::mpi::CommunicatorWithEnvionment& other) :
    //     CommunicatorWithEnvionment(other.env_, other.comm)
    //   {}

    //   ~CommunicatorWithEnvionment() {}
    // };
  }
}

#endif

#endif
