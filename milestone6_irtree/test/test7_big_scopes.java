class Program {
    public static void main() {
        int i;
        i = 5;

        int x;
        x = 0;
        int n;
        n = 6;
        while (x < n) {
            System.out.println(111111111);
            System.out.println(x);
            System.out.println(n);
            int y;
            y = 11;
            while (y < n * 2) {
                System.out.println(222222222);
                System.out.println(x);
                System.out.println(n);
                System.out.println(y);
                int d;
                d = 0;
                if ((x - n / 2) * (x - n / 2) + 
                    (y - n) * (y - n) / 4 < 25) {
                    d = 7;
                }
                System.out.println(123);
                System.out.println(d);
                System.out.println(456);

                if (y < n * 2 - 1) {
                    System.out.println(789);
                    System.out.println(d);
                    System.out.println(987);
                } else {
                    System.out.println(d);
                }
                y = y + 1;
            }
            x = x + 1;
        }

        while (i < 5) {
            if (i % 2 == 0) {
                System.out.println(1337);

            } else {
                System.out.println(420);
            }
            i = i + 1;
        }
        System.out.println(i);

    }
}

