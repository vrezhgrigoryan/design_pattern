#include <iostream>
#include <vector>
#include <memory>

class ISkills
{
public:
    using ISkillsPtr = std::shared_ptr<ISkills>;
    virtual void Attack() = 0;
    virtual void Defence() = 0;
};

class Person : public ISkills
{
public:
    Person(int id, int attack, int defence, int health):
        m_id(id),
        m_attack(attack),
        m_defence(defence),
        m_health(health)
    {}
    void Attack() override
    {
        std::cout << "Person.Attack() id:" << m_id << "\n";
    }
    void Defence() override
    {
        std::cout << "Person.Defence() id:" << m_id << "\n";
    }

private:
    int m_id;
    int m_attack;
    int m_defence;
    int m_health;
};

class Group : public ISkills
{
public:
    using GroupPtr = std::shared_ptr<Group>;
    Group(int id):
        m_id(id)
    {}
    
    void Attack() override
    {
        for(const auto& obj : m_objects)
        {
            obj->Attack();
        }
    }
    void Defence() override
    {
        for(const auto& obj : m_objects)
        {
            obj->Defence();
        }
    }
    
    void AddtoGroup(const ISkillsPtr& obj)
    {
        m_objects.push_back(obj);
    }
    
private:
    int m_id;
    std::vector<ISkillsPtr> m_objects;
};

int main() {
   ISkills::ISkillsPtr p1 = std::make_shared<Person>(1, 2, 3,  10);
   ISkills::ISkillsPtr p2 = std::make_shared<Person>(2, 2, 3, 10); 
    Group::GroupPtr g1 = std::make_shared<Group>(111);
    g1->AddtoGroup(p1);
    
    Group::GroupPtr g2 = std::make_shared<Group>(112);
    g1->AddtoGroup(p2);
    g1->AddtoGroup(g2);
    g1->Attack();
    return 0;
}
