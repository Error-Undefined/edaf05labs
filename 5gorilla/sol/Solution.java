package sol;

import java.util.Scanner;

public class Solution {

  int[][] costMatrix;
  int[] charToIntTable;
  int delta = -4;

  /**
   * Aligns the strings s1 and s2, returns the two aligned strings.
   */
  String align(String s1, String s2) {
    int m = s1.length();
    int n = s2.length();

    // optMatrix: where we store the DP-results.
    // Along the edges, we can safely initialize it as i*delta or j*delta
    int[][] optMatrix = new int[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
      optMatrix[i][0] = delta * i;
    }

    for (int j = 0; j <= n; j++) {
      optMatrix[0][j] = delta * j;
    }

    // Creating the optMatrix. This part has time complexity O(m*n)
    // and thus the whole alignment algorithm is also O(m*n)
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        // Get the characters
        char c1 = s1.charAt(i - 1);
        char c2 = s2.charAt(j - 1);

        int index1 = charToIntTable[c1 - 'A'];
        int index2 = charToIntTable[c2 - 'A'];

        // Compute the three possible costs
        int cost1 = costMatrix[index1][index2] + optMatrix[i - 1][j - 1]; // Don't insert anything
        int cost2 = delta + optMatrix[i][j - 1]; // Insert a '*' in s2
        int cost3 = delta + optMatrix[i - 1][j]; // Insert a '*' in s1

        // We use the max as we want as high of a score as possible
        optMatrix[i][j] = Math.max(cost1, Math.max(cost2, cost3));
      }
    }

    // Construct the new string
    int i = m;
    int j = n;

    StringBuilder sb1 = new StringBuilder();
    StringBuilder sb2 = new StringBuilder();

    // We go back through the matrix and find the path to take for minimal cost
    // Creating the words as we go by using the stringbuilders
    while (!(i == 0 || j == 0)) {
      char c1 = s1.charAt(i - 1);
      char c2 = s2.charAt(j - 1);
      int index1 = charToIntTable[c1 - 'A'];
      int index2 = charToIntTable[c2 - 'A'];

      if (optMatrix[i - 1][j - 1] + costMatrix[index1][index2] == optMatrix[i][j]) {
        sb1.append(c1);
        sb2.append(c2);
        i--;
        j--;
        // Case misaligned, insert * into second string
      } else if (optMatrix[i - 1][j] + delta == optMatrix[i][j]) {
        sb1.append(c1);
        sb2.append('*');
        i--;
        // Case misaligned, insert * into first string
      } else if (optMatrix[i][j - 1] + delta == optMatrix[i][j]) {
        sb1.append('*');
        sb2.append(c2);
        j--;
      }

    }

    // If we reach for i or j, we have reached the edge of the optMatrix.
    // Then, the string which has no more characters to fill is padded with '*'
    // The other one is filled with the remaining characters.
    while (j != 0 && i == 0) {
      sb1.append('*');
      sb2.append(s2.charAt(j - 1));
      j--;
    }

    while (j == 0 && i != 0) {
      sb1.append(s1.charAt(i - 1));
      sb2.append('*');
      i--;
    }

    // We built the strings backwards so we reverse them
    sb1.reverse();
    sb2.reverse();

    sb1.append(" ");
    sb1.append(sb2);

    return sb1.toString();
  }

  void run() {
    // long t0 = System.currentTimeMillis();

    Scanner scan = new Scanner(System.in);
    String alphabet;

    alphabet = scan.nextLine();
    // The regex "\\s" is built in in Java and matches to whitespace
    alphabet = alphabet.replaceAll("\\s", "");

    // System.out.println(alphabet);
    int letters = alphabet.length();

    // System.out.println(alphabet.length());

    costMatrix = new int[letters][letters];

    for (int i = 0; i < letters; i++) {
      for (int j = 0; j < letters; j++) {
        costMatrix[i][j] = scan.nextInt();
      }
    }

    // We create a lookup table where we can convert a character in a word to use as
    // an index in the cost matrix. Its length is 26 as we have 26 possible letters.
    charToIntTable = new int[26];
    for (int i = 0; i < letters; i++) {
      char c = alphabet.charAt(i);

      // A capital A has ASCII value 65, and thus
      // we subtract A from the char to convert A to index 0, B to index 1, etc.
      int index = c - 'A';
      charToIntTable[index] = i;
    }

    int Q = scan.nextInt();
    scan.nextLine();
    // long algoTime = 0;

    for (int i = 0; i < Q; i++) {
      String input = scan.nextLine();
      String[] splitInTwo = input.split("[\\s]");

      String s1 = splitInTwo[0];
      String s2 = splitInTwo[1];

      // long t1 = System.currentTimeMillis();
      System.out.println(align(s1, s2));
      // long t2 = System.currentTimeMillis();
      // algoTime += (t2 - t1);
    }

    scan.close();

    // long tEnd = System.currentTimeMillis();
    // tEnd -= t0;

    // System.out.println("Total time: " + tEnd + "ms");
    // System.out.println("Algo time: " + algoTime + "ms");
  }

  public static void main(String[] args) {
    Solution sol = new Solution();
    sol.run();
  }
}