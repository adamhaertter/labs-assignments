package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Common {

    /**
     * Given two matrices, performs matrix addition by adding the values in the
     * corresponding cells together.
     * 
     * @param A The first matrix
     * @param B The second matrix
     * @return a resulting matrix where each cell is the sum of the values in the
     *         input cells.
     */
    public static int[][] matAddition(int[][] A, int[][] B) {
	int n = A.length;
	int[][] C = new int[A.length][A[0].length];

	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		C[i][j] = A[i][j] + B[i][j];
	    }
	}
	return C;
    }

    /**
     * Given two matrices, performs matrix subtraction by subtracting the values in
     * the corresponding cells of matrix B from matrix A. Subtraction is performed
     * in the order A - B.
     * 
     * @param A The first matrix
     * @param B The second matrix
     * @return a resulting matrix where each cell is the difference of the values in
     *         the input cells.
     */
    public static int[][] matSubtract(int[][] A, int[][] B) {
	int n = A.length;
	int[][] C = new int[A.length][A[0].length];

	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		C[i][j] = A[i][j] - B[i][j];
	    }
	}
	return C;
    }

    /**
     * Reads all of the matrix pairs from a given file. Files must be comma
     * delimited and in the format provided by Dr. Armstrong. Matrix pairs are
     * returned in a 3D array, or essentially an array of matrices.
     * 
     * Pairs are sequential (ex. result[0] and result[1] are a pair, result[2] and
     * result[3], etc.)
     * 
     * @param fileName the name of the csv file to be parsed for matrices
     * @return a 3-Dimensional array, or an array of all the matrices parsed from
     *         the file.
     * @throws FileNotFoundException
     */
    public static int[][][] readAllMatrices(String fileName) throws FileNotFoundException {
	// Setting up the Scanner
	File file = new File(fileName);
	Scanner scanner = new Scanner(file);
	scanner.useDelimiter(","); // These are csv files, so they are separated by commas

	int n, matrixSize, numberOfPairs;

	scanner.nextLine(); // consume the first line, we don't need the headers
	n = Integer.parseInt(scanner.next());
	matrixSize = Integer.parseInt(scanner.next());
	numberOfPairs = Integer.parseInt(scanner.next());
	scanner.nextLine(); // finishes off the line, likely to be empty

	int[][][] matrixList = new int[numberOfPairs * 2][matrixSize][matrixSize];
	for (int numMatrices = 0; numMatrices < matrixList.length; numMatrices++) {
	    matrixList[numMatrices] = pullMatrixFromFile(scanner, matrixSize);
	    scanner.nextLine();
	}

	scanner.close();

	return matrixList;
    }

    /**
     * Pulls a single matrix from a comma delimited file.
     * 
     * @param scanner         The object of type Scanner set to parse through some
     *                        file.
     * @param matrixDimension one dimension of the evenly-sized matrix.
     * @return the matrix starting at the point the scanner is pointing at
     */
    public static int[][] pullMatrixFromFile(Scanner scanner, int matrixDimension) {
	int[][] matrix = new int[matrixDimension][matrixDimension];
	// Read Singular Matrix
	String[] splitRow;
	for (int row = 0; row < matrixDimension; row++) {
	    splitRow = scanner.nextLine().split(",");
	    for (int col = 0; col < matrixDimension; col++) {
		matrix[row][col] = Integer.parseInt(splitRow[col]);
	    }
	}
	return matrix;
    }
}
