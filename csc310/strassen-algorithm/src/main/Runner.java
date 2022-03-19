package main;

import java.io.FileNotFoundException;
import java.io.IOException;

public class Runner {

    public static void main(String args[]) {
	// createMatrixFile(20, 10);
	testFormal();
    }

    /**
     * The formal test process as outlined by the assignment document. Reads in
     * matrices from a file named "input.csv" in root. Then reports the times it
     * takes for these matrix pairs to be multiplied by the brute force algorithm
     * and the combined algorithm. The combined algorithm will run and report for n
     * times, where n is the power of two used in the dimension of said matrices.
     * 
     * All results are output and formatted to the console.
     * 
     */
    public static void testFormal() {
	int[][][] totalOutput;

	try {
	    totalOutput = Common.readAllMatrices("input.csv");
	} catch (FileNotFoundException e) {
	    e.printStackTrace();
	    System.out.println("Unable to read matrices from file. Cancelling operation.");
	    return;
	}

	// Print Brute Force Test Results
	System.out.println("Brute Force test results: ");
	long startTime;
	for (int i = 0; i < totalOutput.length / 2; i++) {
	    startTime = System.currentTimeMillis();
	    BruteForce.matMultiply(totalOutput[2 * i], totalOutput[2 * i + 1]);
	    System.out.print("Pair " + (i + 1) + ": " + (System.currentTimeMillis() - startTime) + " ms | ");
	}
	System.out.println();
	System.out.println();

	// Initialize instance of combined algorithm
	Combined mixAlgorithm = new Combined(1);

	// Get the power nf from matrix of dimension 2^(nf) x 2^(nf)
	int maxCutoff = (int) (Math.log10(totalOutput[0].length) / Math.log10(2));

	for (int cutoff = 1; cutoff <= maxCutoff; cutoff++) {
	    mixAlgorithm.setCutoff(cutoff);
	    System.out.println("Strassen test results with cutoff " + cutoff + ": ");
	    for (int i = 0; i < totalOutput.length / 2; i++) {
		startTime = System.currentTimeMillis();
		mixAlgorithm.matMultiply(totalOutput[2 * i], totalOutput[2 * i + 1]);
		System.out.print("Pair " + (i + 1) + ": " + (System.currentTimeMillis() - startTime) + " ms | ");
	    }
	    System.out.println();
	}
    }

    /**
     * @author Adam Haertter
     * 
     *         Creates a file "output.csv" in the project's root folder. WARNING:
     *         Will overwrite any output.csv file present in root without asking.
     * 
     * @param numPairs   The number of matrix pairs to create. Giving 2 will
     *                   generate 4 matrices.
     * @param powerOfTwo The exponential value n to generate a 2^n x 2^n matrix.
     * @return true on successful run, false if an error occurs.
     */
    public static boolean createMatrixFile(int numPairs, int powerOfTwo) {
	int matSize = (int) Math.pow(2, powerOfTwo);

	java.io.File file = new java.io.File("input.csv");
	try {
	    file.createNewFile();
	    System.out.println("output.csv has been created successfully in root.");
	} catch (IOException e) {
	    System.out.println("output.csv already exists in root, overwriting...");
	}

	java.io.FileWriter writer;

	try {
	    writer = new java.io.FileWriter(file);

	    // Header set-up
	    writer.append("n");
	    writer.append(",");
	    writer.append("2^n");
	    writer.append(",");
	    writer.append("number of pairs");
	    writer.append(",");
	    for (int i = 5; i < matSize; i++) {
		writer.append(",");
	    }
	    writer.append("\n");

	    // Valued row set-up
	    writer.append("" + powerOfTwo);
	    writer.append(",");
	    writer.append("" + matSize);
	    writer.append(",");
	    writer.append("" + numPairs);
	    writer.append(",");
	    for (int i = 5; i < matSize; i++) {
		writer.append(",");
	    }
	    writer.append("\n");

	    for (int matCount = 1; matCount <= numPairs * 2; matCount++) {
		// Write matrix
		for (int i = 1; i <= matSize; i++) {
		    for (int j = 1; j <= matSize; j++) {
			writer.append("" + (int) (Math.random() * 10));
			if (j != matSize)
			    writer.append(",");
			else
			    writer.append("\n");
		    }
		}

		// Write arraycount
		writer.append("~" + matCount);
		for (int i = 0; i < matSize; i++) {
		    writer.append(",");
		}
		writer.append("\n");
	    }

	    // Write termination sequence
	    writer.append("###");
	    for (int i = 0; i < matSize; i++) {
		writer.append(",");
	    }

	    // End the writer
	    writer.flush();
	    writer.close();
	} catch (IOException e) {
	    e.printStackTrace();
	    return false;
	}

	return true;
    }

    /**
     * The informal test process as outlined by the documentation. Generates two
     * random matrices and then reports the time it takes for them to be multiplied
     * by the brute force algorithm, Strassen's algorithm, and a combined algorithm
     * with a cutoff of half the matrix size.
     * 
     * @param powerOfTwo the value n to be used in creating a 2^n by 2^n matrix
     */
    public static void testInformal(int powerOfTwo) {
	int[][] A = randomMatrix(powerOfTwo);
	int[][] B = randomMatrix(powerOfTwo);
	Combined mix = new Combined(powerOfTwo / 2);
	System.out.println("Informal test process for two matrices size 2^" + powerOfTwo);

	long startTime = System.currentTimeMillis();
	BruteForce.matMultiply(A, B);
	System.out.println("Time for Brute Force: " + (System.currentTimeMillis() - startTime) + " ms");

	startTime = System.currentTimeMillis();
	mix.matMultiply(A, B);
	System.out.print("Time for mixed algorithm: " + (System.currentTimeMillis() - startTime) + " ms");
	System.out.println(", where cutoff = " + powerOfTwo / 2);

	startTime = System.currentTimeMillis();
	Strassen.matMultiply(A, B);
	System.out.println("Time for full Strassen's: " + (System.currentTimeMillis() - startTime) + " ms");

    }

    /**
     * Returns a random matrix of size 2^n by 2^n, where n is provided as input.
     * This method is used for informal testing purposes.
     * 
     * @param powerOfTwo the value n to be used in creating a 2^n by 2^n matrix
     * @return a matrix of specified size filled with random numbers 0-9
     */
    public static int[][] randomMatrix(int powerOfTwo) {
	int size = (int) Math.pow(2, powerOfTwo);
	int[][] matrix = new int[size][size];
	for (int i = 0; i < size; i++) {
	    for (int j = 0; j < size; j++) {
		matrix[i][j] = (int) (Math.random() * 10);
	    }
	}
	return matrix;
    }
}
