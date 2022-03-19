package main;

import java.util.function.BinaryOperator;

public class Strassen {

    /**
     * Runs Strassen's Algorithm for matrix multiplication on two given matrices.
     * This implementation will recurse down to single-celled matrices.
     * 
     * @param A the first matrix
     * @param B the second matrix
     * @return the resulting matrix after undergoing Strassen's matrix
     *         multiplication
     */
    public static int[][] matMultiply(int[][] A, int[][] B) {
	int[][] C = new int[A.length][A[0].length];
	BinaryOperator<int[][]> recurse = (one, two) -> matMultiply(one, two);

	if (C.length <= 1) {
	    C[0][0] = A[0][0] * B[0][0];
	} else {
	    C = loopOnce(A, B, recurse);
	}

	return C;
    }

    /**
     * Performs a single loop of Strassen's algorithm for multiplying matrices A and
     * B. Requires a BinaryOperator to specify which parent method to recurse back
     * through, as this method does not contain an exit case for recursion.
     * 
     * @param A the first matrix
     * @param B the second matrix
     * @param recurse a BinaryOperator specifying which method the recursive calls of this method should lead to. Necessary for differentiating full Strassen's vs. a custom cutoff point.
     * @return the result of matrix multiplication through so many loops of Strassen's algorithm.
     */
    public static int[][] loopOnce(int[][] A, int[][] B, BinaryOperator<int[][]> recurse) {
	int n = A.length;
	int[][] C = new int[n][n];
	// Sub-Matrices
	int[][] A00 = new int[n / 2][n / 2];
	int[][] A01 = new int[n / 2][n / 2];
	int[][] A10 = new int[n / 2][n / 2];
	int[][] A11 = new int[n / 2][n / 2];

	int[][] B00 = new int[n / 2][n / 2];
	int[][] B01 = new int[n / 2][n / 2];
	int[][] B10 = new int[n / 2][n / 2];
	int[][] B11 = new int[n / 2][n / 2];

	// Fill the sub-matrices
	for (int i = 0; i < n / 2; i++) {
	    for (int j = 0; j < n / 2; j++) {
		// Top Left
		A00[i][j] = A[i][j];
		B00[i][j] = B[i][j];

		// Top Right
		A01[i][j] = A[i][n / 2 + j];
		B01[i][j] = B[i][n / 2 + j];

		// Bottom Left
		A10[i][j] = A[n / 2 + i][j];
		B10[i][j] = B[n / 2 + i][j];

		// Bottom Right
		A11[i][j] = A[n / 2 + i][n / 2 + j];
		B11[i][j] = B[n / 2 + i][n / 2 + j];
	    }
	}

	// Generating Strassen's Formulas Recursively
	int[][] m1 = recurse.apply(Common.matAddition(A00, A11), Common.matAddition(B00, B11));
	int[][] m2 = recurse.apply(Common.matAddition(A10, A11), B00);
	int[][] m3 = recurse.apply(A00, Common.matSubtract(B01, B11));
	int[][] m4 = recurse.apply(A11, Common.matSubtract(B10, B00));
	int[][] m5 = recurse.apply(Common.matAddition(A00, A01), B11);
	int[][] m6 = recurse.apply(Common.matSubtract(A10, A00), Common.matAddition(B00, B01));
	int[][] m7 = recurse.apply(Common.matSubtract(A01, A11), Common.matAddition(B10, B11));

	// Setting up C's sub-matrices
	int[][] C00 = Common.matAddition(Common.matSubtract(Common.matAddition(m1, m4), m5), m7);
	int[][] C01 = Common.matAddition(m3, m5);
	int[][] C10 = Common.matAddition(m2, m4);
	int[][] C11 = Common.matAddition(Common.matSubtract(Common.matAddition(m1, m3), m2), m6);

	// Combining sub-matrices into returnable matrix
	for (int i = 0; i < n / 2; i++) {
	    for (int j = 0; j < n / 2; j++) {
		// Top Left
		C[i][j] = C00[i][j];

		// Top Right
		C[i][n / 2 + j] = C01[i][j];

		// Bottom Left
		C[n / 2 + i][j] = C10[i][j];

		// Bottom Right
		C[n / 2 + i][n / 2 + j] = C11[i][j];
	    }
	}
	return C;
    }
}
