class Main {
  public static void main() {
    boolean res;

    res = new Dummy().AlwaysTrue();
    System.out.println(res);
    res = new Dummy().AlwaysTrue();
    System.out.println(res);

    res = new Dummy().AlwaysFalse();
    System.out.println(res);
    res = new Dummy().AlwaysFalse();
    System.out.println(res);
  }
}

class Dummy {
  public boolean AlwaysTrue() {
    return 1;
  }

  public boolean AlwaysFalse() {
    if (true) {
      return 0;
    }

    return 1;
  }
}
