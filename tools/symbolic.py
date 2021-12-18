#!/usr/bin/env python3
from sympy import *

# Declare symbols
var('w00 w01 w02 w03 w10 w11 w12 w13 w20 w21 w22 w23 w30 w31 w32 w33')
var('h00 h01 h02 h03 h10 h11 h12 h13 h20 h21 h22 h23 h30 h31 h32 h33')
var('k00 k01 k02 k10 k11 k12 k20 k21 k22')

# Declare matrices
# const cv::Mat A = (cv::Mat_<float>(4, 2) << 1, 0, 1, 1, 1, -1, 0, -1);
# const cv::Mat B = (cv::Mat_<float>(4, 4) << 1, 0, 0, 0, 0, 1, -1, 1, -1, 1, 1, 0, 0, 0, 0, -1);
# const cv::Mat G = (cv::Mat_<float>(4, 3) << 1, 0, 0, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0, 0, 1);
A = Matrix([[1, 0],[1, 1],[1, -1],[0, -1]])
B = Matrix([[1, 0, 0, 0],[0, 1, -1, 1],[-1, 1, 1, 0],[0, 0, 0, -1]])
G = Matrix([[1, 0, 0],[0.5, 0.5, 0.5],[0.5, -0.5, 0.5], [0, 0, 1]])

# Declare symbolic matrices
W = Matrix([[w00,w01,w02,w03],[w10,w11,w12,w13],[w20, w21,w22,w23],[w30,w31,w32,w33]])
K = Matrix([[k00,k01,k02],[k10,k11,k12],[k20,k21,k22]])
H = Matrix([[h00,h01,h02,h03],[h10,h11,h12,h13],[h20,h21,h22,h23],[h30,h31,h32,h33]])

# Compute
# const cv::Mat GfGt = G * kernel * G.t();
# cv::Mat BtZB = B.t() * inputf(iroi) * B;
# O = A.t() * (GfGt.mul(BtZB)) * A;
BtZB = B.T * W * B
GfGt = G * K * G.T
Hadamard = matrix_multiply_elementwise(GfGt, BtZB)
O = A.T * Hadamard * A
OH = A.T * H * A

# 0: k0*(w0 + w10 - w2 - w8) + (0.5*k0 - 0.5*k1 + 0.5*k2)*(-w1 - w10 + w2 + w9) + (0.5*k0 + 0.5*k1 + 0.5*k2)*(w1 - w10 + w2 - w9) + (0.5*k0 - 0.5*k3 + 0.5*k6)*(-w10 - w4 + w6 + w8) + (0.5*k0 + 0.5*k3 + 0.5*k6)*(-w10 + w4 - w6 + w8) + (w10 - w5 - w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 - 0.25*k3 - 0.25*k4 - 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8) + (w10 - w5 + w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 + 0.25*k3 - 0.25*k4 + 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) + (w10 + w5 - w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 - 0.25*k3 + 0.25*k4 - 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) + (w10 + w5 + w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 + 0.25*k3 + 0.25*k4 + 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8)
# 1: -k2*(w1 + w11 - w3 - w9) - (0.5*k0 - 0.5*k1 + 0.5*k2)*(-w1 - w10 + w2 + w9) + (0.5*k0 + 0.5*k1 + 0.5*k2)*(w1 - w10 + w2 - w9) - (0.5*k2 - 0.5*k5 + 0.5*k8)*(-w11 - w5 + w7 + w9) - (0.5*k2 + 0.5*k5 + 0.5*k8)*(-w11 + w5 - w7 + w9) + (w10 - w5 - w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 - 0.25*k3 - 0.25*k4 - 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8) - (w10 - w5 + w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 + 0.25*k3 - 0.25*k4 + 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) - (w10 + w5 - w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 - 0.25*k3 + 0.25*k4 - 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) + (w10 + w5 + w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 + 0.25*k3 + 0.25*k4 + 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8)
# 2: -k6*(-w12 + w14 + w4 - w6) - (0.5*k0 - 0.5*k3 + 0.5*k6)*(-w10 - w4 + w6 + w8) + (0.5*k0 + 0.5*k3 + 0.5*k6)*(-w10 + w4 - w6 + w8) - (0.5*k6 - 0.5*k7 + 0.5*k8)*(w13 - w14 - w5 + w6) - (0.5*k6 + 0.5*k7 + 0.5*k8)*(-w13 - w14 + w5 + w6) - (w10 - w5 - w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 - 0.25*k3 - 0.25*k4 - 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8) + (w10 - w5 + w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 + 0.25*k3 - 0.25*k4 + 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) - (w10 + w5 - w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 - 0.25*k3 + 0.25*k4 - 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) + (w10 + w5 + w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 + 0.25*k3 + 0.25*k4 + 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8)
# 3: k8*(-w13 + w15 + w5 - w7) + (0.5*k2 - 0.5*k5 + 0.5*k8)*(-w11 - w5 + w7 + w9) - (0.5*k2 + 0.5*k5 + 0.5*k8)*(-w11 + w5 - w7 + w9) + (0.5*k6 - 0.5*k7 + 0.5*k8)*(w13 - w14 - w5 + w6) - (0.5*k6 + 0.5*k7 + 0.5*k8)*(-w13 - w14 + w5 + w6) - (w10 - w5 - w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 - 0.25*k3 - 0.25*k4 - 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8) - (w10 - w5 + w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 + 0.25*k3 - 0.25*k4 + 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) + (w10 + w5 - w6 - w9)*(0.25*k0 - 0.25*k1 + 0.25*k2 - 0.25*k3 + 0.25*k4 - 0.25*k5 + 0.25*k6 - 0.25*k7 + 0.25*k8) + (w10 + w5 + w6 + w9)*(0.25*k0 + 0.25*k1 + 0.25*k2 + 0.25*k3 + 0.25*k4 + 0.25*k5 + 0.25*k6 + 0.25*k7 + 0.25*k8)

print("--Space -> Winograd--")
print("\n")
S_BtZB = simplify(BtZB)
S_GfGt = simplify(GfGt)
S_hadamard = simplify(Hadamard)
S_OH = simplify(OH)
print("Input transform: ")
print(S_BtZB)
print("\n")
print("Kernel transform: ")
print(S_GfGt)
print("\n")
print("Hadamard: ")
print(S_hadamard)
print("OH: ")
print(S_OH)
print("\n\n")

print("--Simplificado--")
S0 = simplify(O)
print(S0[0,0])
print(S0[0,1])
print(S0[1,0])
print(S0[1,1])
