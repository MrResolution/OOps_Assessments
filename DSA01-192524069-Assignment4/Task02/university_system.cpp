#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n, int i, const std::string& p)
        : name(n), id(i), phone(p) {}
    virtual ~Person() = default;

    virtual void display() const {
        std::cout << "ID: " << id << " | Name: " << name << " | Phone: " << phone << "\n";
    }

    std::string getName() const { return name; }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p, const std::string& prog, double g)
        : Person(n, i, p), programme(prog), cgpa(g) {}

    void display() const override {
        Person::display();
        std::cout << "  [Student] Programme: " << programme << " | CGPA: " << cgpa << "\n";
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p, const std::string& dept, double sal)
        : Person(n, i, p), department(dept), salary(sal) {}

    void display() const override {
        Person::display();
        std::cout << "  [Staff] Dept: " << department << " | Salary: Rs " << salary << "\n";
    }
};

class TeachingAssistant : public Student, public Staff {
    int weeklyTeachingHours;

public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double g,
                      const std::string& dept, double sal,
                      int hours)
        : Person(n, i, p),
          Student(n, i, p, prog, g),
          Staff(n, i, p, dept, sal),
          weeklyTeachingHours(hours) {}

    void display() const override {
        Person::display();
        std::cout << "  [Role: Teaching Assistant]\n";
        std::cout << "  Enrolled in: " << programme << " (CGPA: " << cgpa << ")\n";
        std::cout << "  Employed in: " << department << " (Stipend: Rs " << salary << ")\n";
        std::cout << "  Assigned Teaching: " << weeklyTeachingHours << " hrs/week\n";
    }
};

class ResearchScholar : public Student {
    double fellowshipAmount;

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double g, double fellowship)
        : Person(n, i, p), Student(n, i, p, prog, g), fellowshipAmount(fellowship) {}

    void display() const override {
        Student::display();
        std::cout << "  [Scholar] Fellowship: Rs " << fellowshipAmount << "/month\n";
    }
};

int main() {
    TeachingAssistant ta("Sandip Singh", 101, "9876543210",
                          "M.Tech CSE", 9.4, "Computer Science", 25000, 10);

    ResearchScholar rs("Pooja", 102, "9123456780",
                       "Ph.D AI", 9.8, 37000);

    std::cout << "=== University People Management ===\n\n";
    ta.display();
    std::cout << "\n";
    rs.display();

    return 0;
}
