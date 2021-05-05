class Main {
  public static void main() {
    Number n;
    n = new Number();
    n.SetNumber(0);

    Five f;
    f = new Five();

    while(n.GetNumber() < f.GetNumber()) {
      System.out.println(n.GetNumber());
      n.SetNumber(n.GetNumber() + 1);
    }
  }
}

class Five {
  public int GetNumber() {
    return 5;
  }
}

class Number {
  int value;

  public int GetNumber() {
    return value;
  }

  public void SetNumber(int new_value) {
    value = new_value;
  }
}
