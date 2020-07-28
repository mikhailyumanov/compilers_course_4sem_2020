class Main {
  public static void main() {
    Five a;
    a = new Five();
    Six b;
    b = new Six();
    System.out.println(a.GetNum() + b.GetNum());
  }
}

class Five {
  public int GetNum() {
    return 5;
  }
}

class Six {
  public int GetNum() {
    return 6;
  }
}
