#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>
#include <iostream>

namespace py = pybind11;


void softmax_regression_epoch_cpp(const float *X, const unsigned char *y,
								  float *theta, size_t m, size_t n, size_t k,
								  float lr, size_t batch)
{
    /**
     * A C++ version of the softmax regression epoch code.  This should run a
     * single epoch over the data defined by X and y (and sizes m,n,k), and
     * modify theta in place.  Your function will probably want to allocate
     * (and then delete) some helper arrays to store the logits and gradients.
     *
     * Args:
     *     X (const float *): pointer to X data, of size m*n, stored in row
     *          major (C) format
     *     y (const unsigned char *): pointer to y data, of size m
     *     theta (float *): pointer to theta data, of size n*k, stored in row
     *          major (C) format
     *     m (size_t): number of examples
     *     n (size_t): input dimension
     *     k (size_t): number of classes
     *     lr (float): learning rate / SGD step size
     *     batch (int): SGD minibatch size
     *
     * Returns:
     *     (None)
     */

    /// BEGIN YOUR CODE
    int i,j,a, b;

    for (i = 0; i < m/batch; i++)
    {
      float *Z = new float[batch * k]{};
      float *Xt = new float[n * m]{};
      float *d_theta = new float[n * k]{};
      float *sum_exp = new float[batch]{};

      for (j = i*batch; j < (i+1) * batch; j++)
      {
        for ( a = 0; a < k; a++)
        {
          for (b = 0; b < n; b++)
          {
            Z[(j- i*batch) * k + a] += X[j*n + b] * theta[  b * k + a];
          }
        }

        for (b = 0; b < n; b++)
        {
          Xt[b * m + (j- i*batch)] = X[j * n + b];
        }
      }

      for (j = 0; j < batch; j++)
      {
        for (a = 0; a < k; a ++)
        {
            Z[j * k + a] = std::exp(Z[j * k + a] );
            sum_exp[j] += Z[j * k + a];
        }
      }

      for (j = 0; j < batch; j++)
      {
        for (a = 0; a < k; a ++)
        {
            Z[j * k + a] /= sum_exp[j];
        }
      }

      for (j = i*batch; j < (i+1) * batch; j++)
      {
        for ( a = 0; a < k; a++)
        {
          Z[(j- i*batch) * k + a] -= (y[j] == a)? 1 : 0;
        }
      }

      for (j = 0; j < batch; j++)
      {
        for (a = 0; a < k; a ++)
        {
          for (b = 0; b < n; b++)
          {
            d_theta[b * k + a] += Xt[b * m + j] * Z[j * k + a];
          }
        }
      }
      for (a = 0; a < k; a ++)
      {
        for (b = 0; b < n; b++)
        {
          theta[b * k + a] -= lr * d_theta[b * k + a]/batch;
        }
      }
      delete [] Z;
      delete [] Xt;
      delete [] d_theta;
      delete [] sum_exp;
    }


    /// END YOUR CODE
}


/**
 * This is the pybind11 code that wraps the function above.  It's only role is
 * wrap the function above in a Python module, and you do not need to make any
 * edits to the code
 */
PYBIND11_MODULE(simple_ml_ext, m) {
    m.def("softmax_regression_epoch_cpp",
    	[](py::array_t<float, py::array::c_style> X,
           py::array_t<unsigned char, py::array::c_style> y,
           py::array_t<float, py::array::c_style> theta,
           float lr,
           int batch) {
        softmax_regression_epoch_cpp(
        	static_cast<const float*>(X.request().ptr),
            static_cast<const unsigned char*>(y.request().ptr),
            static_cast<float*>(theta.request().ptr),
            X.request().shape[0],
            X.request().shape[1],
            theta.request().shape[1],
            lr,
            batch
           );
    },
    py::arg("X"), py::arg("y"), py::arg("theta"),
    py::arg("lr"), py::arg("batch"));
}
