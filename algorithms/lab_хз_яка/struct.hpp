#ifndef LAB2_STRUCT_HPP
#define LAB2_STRUCT_HPP


/*
 * Вариант 3
 * Предметная область  Отдел кадров
 * Объекты  Подразделения, Сотрудники
 * Примечание  Имеется  множество
 * подразделений  предприятия.  В
 * каждом  подразделении  работает
 * множество сотрудников.
 * */


#include <vector>
#include <string>


namespace lab {
    
    
    struct Employee {
        std::string name;
    };


    struct Department {

        [[nodiscard]]
        auto size() const noexcept -> int {
            return employees.size();
        }

        std::string name;
        std::vector<Employee> employees;
    };


    struct Company {

        [[nodiscard]]
        auto size() const noexcept {
            int size = 0;
            for (const auto &department : departments) {
                size += department.size();
            }

            return size;
        }

        std::string name;
        std::vector<Department> departments;
    };


    bool operator< (const Company& lhs, const Company& rhs) {
        return lhs.name < rhs.name;
    }

    bool operator== (const Company& lhs, const Company& rhs) {
        return lhs.departments == rhs.departments  && lhs.name == rhs.name;
    }

    bool operator> (const Company& lhs, const Company& rhs) {
        return lhs.name > rhs.name;
    }

    bool operator< (const Department& lhs, const Department& rhs) {
        return lhs.size() < rhs.size();
    }

    bool operator == (const Department& lhs, const Department& rhs){
        return lhs.name == rhs.name && lhs.employees == rhs.employees;
    }

    bool operator> (const Department& lhs, const Department& rhs) {
        return lhs.size() > rhs.size();
    }

    bool operator == (const Employee& lhs, const Employee& rhs){
        return lhs.name == rhs.name;
    }

    template<class OStream>
    OStream& operator<<(OStream& os, const Company& company){
        os << company.name << " : " << company.departments.size() << " departments";
    }

}
#endif //LAB2_STRUCT_HPP
