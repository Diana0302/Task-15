#include <iostream>
#include <vector>
#include <fstream>

  class SortingStrategy {
public:
    virtual void sort(std::vector<int>& arr) = 0;
    virtual ~SortingStrategy() {}
};

class BubbleSort : public SortingStrategy {
public:
    void sort(std::vector<int>& arr) override {
        int size = arr.size();
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

class SelectionSort : public SortingStrategy {
public:
    void sort(std::vector<int>& arr) override {
        int size = arr.size();
        for (int i = 0; i < size - 1; ++i) {
            int min = i;
            for (int j = i + 1; j < size; ++j) {
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            std::swap(arr[i], arr[min]);
        }
    }
};

class FileHandler {
public:
    std::vector<int> read(std::string& file_name) {
        std::vector<int> arr;
        std::ifstream inputFile(file_name);

        int val;
        while (inputFile >> val) {
            arr.push_back(val);
        }

        return arr;
    }


    void save( std::string& file_name,std::vector<int>& arr) {
        std::ofstream outputFile(file_name);

        if (outputFile.is_open()) {
            for (auto i = arr.begin(); i != arr.end(); ++i) {
                outputFile << *i << " ";
            }
            outputFile.close();
            std::cout << "Array save" << std::endl;
        }
        else {
            std::cout << "Error" << std::endl;
        }
    }
};

class SortingApplication {
private:
    SortingStrategy* str;
    FileHandler handler;

public:
    SortingApplication() 
    {
        str = nullptr;
    }

    ~SortingApplication() {
        delete str;
    }

    void prompt() {
        std::cout << "Enter input file name: ";
        std::string inputFile;
        std::cin >> inputFile;

        std::cout << "Enter output file name: ";
        std::string outputFile;
        std::cin >> outputFile;

        std::cout << "if you want to see Bublle Sorting alhorithm choose 1,  for Selection Sorting 2): ";
        int a;
        std::cin >> a;
        setSortingStrategy(a);
        f(inputFile, outputFile);
    }

    void setSortingStrategy(int a) {
        delete str;
        switch (a) {
        case 1:
            str = new BubbleSort();
            break;
        case 2:
            str = new SelectionSort();
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
        }
    }


    void f(std::string& inputFile,std::string& outputFile) {
        std::vector<int> arr1 = handler.read(inputFile);
        if (str) {
            str->sort(arr1);
        }
        else {
            std::cout << "Error" << std::endl;
        }
        handler.save(outputFile, arr1);
    }
};

int main() {
    SortingApplication s;
    s.prompt();

    return 0;
}



