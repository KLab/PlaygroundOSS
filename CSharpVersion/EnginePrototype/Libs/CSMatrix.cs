/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace EnginePrototype
{
	public class CSMatrix : ICloneable
	{
        public class CSVector : ICloneable
        {
            private float[] m_vector;

            public float this[int i]
            {
                get { return m_vector[i]; }
            }

            public CSVector(float[] vector)
            {
                m_vector = vector;
            }

            public object Clone()
            {
                return new CSVector((float[])m_vector.Clone());
            }
        }

        private const float EPSILON = 1e-5f;
        private float[] m_matrix;

        public float this[int i, int j]
        {
            get { return m_matrix[4 * i + j]; }
            //private set { m[4 * j + i] = value; }
        }

        public CSMatrix(float[] matrix = null)
        {
            if(matrix != null) {
                if(matrix.Length == 16) {
                    m_matrix = matrix;
                } else {
                    throw new CKLBException("Length must be 16.");
                }
            } else {
                //create a 4x4 identity matrix
                m_matrix = new float[16] {
                    1,  0,  0,  0,
                    0,  1,  0,  0,
                    0,  0,  1,  0,
                    0,  0,  0,  1
                };
            }
        }

        public object Clone()
        {
            return new CSMatrix((float[])m_matrix.Clone());
        }

        public CSMatrix Copy()
        {
            return (CSMatrix)this.Clone();
        }

        public CSMatrix Transposed()
        {
            float[] res = new float[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    res[4 * i + j] = m_matrix[4 * j + i];
                }
            }
            return new CSMatrix(res);
        }

        public CSMatrix Mul(CSMatrix mat)
        {
			float[] res = new float[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    for(int k = 0; k < 4; ++k) {
                        res[4 * j + i] += this[i, k] * mat[k, j];
                    }
                }
            }
            return new CSMatrix(res);
        }

		// Operator overloading is not supported by the compiler yet.
        //public static CSMatrix operator*(CSMatrix A, CSMatrix B)
        //{
        //    return A.Mul(B);
        //}

        public CSVector Mul(CSVector vect)
        {
            float[] res = new float[] { 0, 0, 0, 0 };
            for(int i = 0; i < 4; ++i) {
                for(int k = 0; k < 4; ++k) {
                    res[i] += this[i, k] * vect[k];
                }
            }
            return new CSVector(res);
        }

        //public static CSVector operator *(CSMatrix mat, CSVector vect)
        //{
        //    return mat.Mul(vect);
        //}

        public static float fabs(float f) { return f >= 0 ? f : f*(-1); }

        public CSMatrix Inverse()
        {
            float[] A = m_matrix;
            float[] B = new float[] {
                    1.0f,  0.0f,  0.0f,  0.0f,
                    0.0f,  1.0f,  0.0f,  0.0f,
                    0.0f,  0.0f,  1.0f,  0.0f,
                    0.0f,  0.0f,  0.0f,  1.0f
            };

            for(int y = 0; y < 4; ++y) {
                float n = A[4 * y + y];
                if(fabs(n) < EPSILON) return null;

                for(int x = 0; x < 4; ++x) {
                    A[4 * y + x] /= n;
                    B[4 * y + x] /= n;
                }
                for(int x = 0; x < 4; ++x) {
                    if(x == y) { continue; }
                    n = A[4 * x + y];
                    for(int z = 0; z < 4; ++z) {
                        A[4 * x + z] -= A[4 * y + z] * n;
                        B[4 * x + z] -= B[4 * y + z] * n;
                    }
                }
            }
            return new CSMatrix(B);
        }
    }
}

