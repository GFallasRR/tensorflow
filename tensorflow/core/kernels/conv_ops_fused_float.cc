/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/framework/register_types.h"
#include "tensorflow/core/kernels/conv_ops_fused_impl.h"

namespace tensorflow {

// If we're using the alternative GEMM-based implementation of Conv2D for the
// CPU implementation, don't register this EigenTensor-based version.
// TODO(b/119765980): Upgrade upstream Eigen to set `m_can_use_xsmm=false` for
// contractions with non-default contraction output kernels.
#if !defined(USE_GEMM_FOR_CONV) && !defined(EIGEN_USE_LIBXSMM)
TF_CALL_float(REGISTER_FUSED_CPU_CONV2D);
#endif  // !USE_GEMM_FOR_CONV

#if GOOGLE_CUDA

namespace functor {
DECLARE_FUNCTOR_GPU_SPEC(float);
}  // namespace functor

TF_CALL_float(REGISTER_FUSED_GPU_CONV2D);

#endif  // GOOGLE_CUDA

}  // namespace tensorflow
