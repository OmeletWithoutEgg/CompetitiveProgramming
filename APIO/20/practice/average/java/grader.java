import java.util.ArrayList;
import java.util.List;

public class grader {
  public static void main(String[] args) {
    InputReader inputReader = new InputReader(System.in);
    int Q = inputReader.readInt();

    int[] type = new int[Q];
    int[] K = new int[Q];
    int[] L = new int[Q];
    int[] R = new int[Q];
    for (int i = 0; i < Q; ++i) {
      type[i] = inputReader.readInt();
      if (type[i] == 0) {
        K[i] = inputReader.readInt();
      } else if (type[i] == 1) {
        L[i] = inputReader.readInt();
        R[i] = inputReader.readInt();
      }
    }

    average solver = new average();
    solver.init();

    List<Double> maximumAverages = new ArrayList<Double>();
    for (int i = 0; i < Q; ++i) {
      if (type[i] == 0) {
        solver.addMonth(K[i]);
      } else if (type[i] == 1) {
        maximumAverages.add(solver.maximumAverage(L[i], R[i]));
      }
    }

    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < maximumAverages.size(); ++i) {
      sb.append(String.format("%.9f", maximumAverages.get(i)));
      sb.append('\n');
    }
    System.out.print(sb.toString());
  }
}


class InputReader implements java.io.Closeable {
  private java.io.InputStream stream;
  private byte[] buf = new byte[1024];
  private int curChar;
  private int numChars;

  public InputReader(java.io.InputStream stream) {
    this.stream = stream;
  }
  
  @Override
  public void close() {
    try {
      this.stream.close();
    } catch (java.io.IOException e) {
    }
  }

  public int read() {
    if (numChars == -1) {
      throw new java.util.InputMismatchException();
    }
    if (curChar >= numChars) {
      curChar = 0;
      try {
        numChars = stream.read(buf);
      } catch (java.io.IOException e) {
        throw new java.util.InputMismatchException();
      }
      if (numChars <= 0) {
        return -1;
      }
    }
    return buf[curChar++];
  }

  public int readInt() {
    int c = eatWhite();
    int sgn = 1;
    if (c == '-') {
      sgn = -1;
      c = read();
    }
    int res = 0;
    do {
      if (c < '0' || c > '9') {
        throw new java.util.InputMismatchException();
      }
      res *= 10;
      res += c - '0';
      c = read();
    } while (!isSpaceChar(c));
    return res * sgn;
  }

  public String readString() {
    int c = eatWhite();
    StringBuilder res = new StringBuilder();
    do {
      if (Character.isValidCodePoint(c))
        res.appendCodePoint(c);
      c = read();
    } while (!isSpaceChar(c));
    return res.toString();
  }

  public String readLine() {
    StringBuilder res = new StringBuilder();
    while (true) {
      int c = read();
      if (c == '\n' || c == '\r' || c == -1)
        break;
      if (Character.isValidCodePoint(c))
        res.appendCodePoint(c);
    }
    return res.toString();
  }

  private int eatWhite() {
    int c = read();
    while (isSpaceChar(c)) {
      c = read();
    }
    return c;
  }

  public static boolean isSpaceChar(int c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
  }
}
