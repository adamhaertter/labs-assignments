package main;

import java.util.function.BinaryOperator;

public class Combined {

    private int powerOfTwo;

    /**
     * Creates an object representing the Combined Algorithm. This implementation
     * requires an object be made because of the lambda expression for recursive
     * calls.
     * 
     * @param customPowerLimit the custom cutoff point as a power of two.
     */
    public Combined(int customPowerLimit) {
	powerOfTwo = customPowerLimit;
    }

    /**
     * Performs a combined algorithm of matrix multiplication between Strassen's
     * Algorithm and the Brute-Force approach. This method is NOT static, and the
     * cutoff point must be set through either the constructor or the setCutoff
     * method.
     * 
     * @param A The first matrix
     * @param B The second matrix
     * @return the resulting matrix after undergoing combined matrix multiplication.
     */
    public int[][] matMultiply(int[][] A, int[][] B) {
	int n = A.length;
	int[][] C = new int[n][n];
	BinaryOperator<int[][]> recursiveCall = (one, two) -> matMultiply(one, two);

	if (C.length <= 1) {
	    C[0][0] = A[0][0] * B[0][0];
	} else if (n >= Math.pow(2, powerOfTwo)) {
	    C = Strassen.loopOnce(A, B, recursiveCall);
	} else {
	    C = BruteForce.matMultiply(A, B);
	}

	return C;
    }

    /**
     * Sets a new custom cutoff point for the algorithm so that a new object does
     * not have to be instantiated every time.
     * 
     * @param customPowerLimit the custom cutoff point as a power of two.
     */
    public void setCutoff(int customPowerLimit) {
	powerOfTwo = customPowerLimit;
    }
}
