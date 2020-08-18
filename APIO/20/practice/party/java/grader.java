public class grader {
  private static int N, M, Q;

  private static long[] maleAcquaintances;
  private static long[] femaleAcquaintances;

  private static void wrongAnswer(String message) {
    System.out.printf("WA: %s\n", message);
    System.exit(0);
  }

  public static int[] ask(int[] G) {
    if (--Q < 0) {
      wrongAnswer("Too many queries");
    }
    long males = 0;
    long females = 0;

    int previousIndex = -1;
    for (int i = 0; i < G.length; ++i) {
      if (G[i] <= previousIndex || G[i] >= N + M) {
        wrongAnswer("Invalid index");
      }
      if (G[i] < N) {
        females |= maleAcquaintances[G[i]];
      } else {
        males |= femaleAcquaintances[G[i] - N];
      }
    }

    int[] result = new int[Long.bitCount(males) + Long.bitCount(females)];
    int currentIndex = 0;
    while (males > 0) {
      int maleIndex = Long.numberOfTrailingZeros(males);
      result[currentIndex++] = maleIndex;
      males ^= 1L << maleIndex;
    }
    while (females > 0) {
      int femaleIndex = Long.numberOfTrailingZeros(females);
      result[currentIndex++] = femaleIndex + N;
      females ^= 1L << femaleIndex;
    }
    return result;
  }

  public static void main(String[] args) {
    InputReader inputReader = new InputReader(System.in);
    N = inputReader.readInt();
    M = inputReader.readInt();
    Q = inputReader.readInt();
    maleAcquaintances = new long[N];
    femaleAcquaintances = new long[M];

    for (int i = 0; i < N + M; ++i) {
      String buffer = inputReader.readString();
      for (int j = 0; j < N + M; ++j) {
        if (buffer.charAt(j) == '1') {
          if (i < N) {
            maleAcquaintances[i] |= 1L << (j - N);
          } else {
            femaleAcquaintances[i - N] |= 1L << j;
          }
        }
      }
    }

    party solver = new party();
    int unusualGuest = solver.findUnusualGuest(N, M, Q);

    if (unusualGuest < 0 || unusualGuest >= N + M) {
      wrongAnswer("Invalid index");
    }
    if (unusualGuest < N) {
      if (Long.bitCount(maleAcquaintances[unusualGuest]) == 1) {
        wrongAnswer("Non-unusual guest found");
      }
    } else {
      if (Long.bitCount(femaleAcquaintances[unusualGuest - N]) == 1) {
        wrongAnswer("Non-unusual guest found");
      }
    }

    System.out.println(unusualGuest);
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
