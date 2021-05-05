class Main {
  public static void main() {
    House house;
    house = new House();
    house.SetNumDogs(0);
    house.SetDogs(new Dog[1]);

    if (3 > 2) {
      int i;
      int[] j;
      House h;
      House[] g;
    }

    house.AddDog(42);
    System.out.println(house.GetNumDogs());

    house.AddDog(79);
    System.out.println(house.GetNumDogs());

    house.GetDog(0).Bark();
    house.GetDog(1).Bark();
  }
}

class Dog {
  int dog_index;

  public void SetIndex(int idx) {
    dog_index = idx;
  }

  public void Bark() {
    System.out.println(dog_index);
  }
}

class House {
  Dog[] dogs;
  int num_dogs;

  public void SetNumDogs(int new_num) {
    num_dogs = new_num;
  }

  public int GetNumDogs() {
    return num_dogs;
  }

  public void SetDogs(Dog[] new_dogs) {
    dogs = new_dogs;
  }

  public void AddDog(int dog_index) {
    if (this.GetNumDogs() == dogs.length) {
      Dog[] new_dogs;
      new_dogs = new Dog[num_dogs * 2];
  
      int i;
      i = 0;
      while (i < num_dogs) {
        new_dogs[i] = dogs[i];
        i = i + 1;
      }
      dogs = new_dogs;
    }

    Dog new_dog;
    new_dog = new Dog();
    new_dog.SetIndex(dog_index);
    new_dog.Bark();

    dogs[num_dogs] = new_dog;
    num_dogs = num_dogs + 1;
  }

  public Dog GetDog(int i) {
    assert(i > -1);
    assert(i < num_dogs);

    return dogs[i];
  }
}

class Person {
  Dog[] dogs;

  public void SetDogs(Dog[] new_dogs) {
    dogs = new_dogs;
  }
}
