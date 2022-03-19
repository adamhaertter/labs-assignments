package main;

public class BruteForce {
    
    /**
     * Performs matrix multiplication using a brute-force approach.
     * 
     * @param A The first matrix
     * @param B The second matrix
     * @return the resulting matrix after undergoing brute-force matrix multiplication.
     */
    public static int[][] matMultiply(int[][] A, int[][] B) {
	int n = A.length;
	int[][] C = new int[n][n];

	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		C[i][j] = 0;
		for (int k = 0; k < n; k++) {
		    C[i][j] = C[i][j] + A[i][k] * B[k][j];
		}
	    }
	}

	return C;
    }
}
