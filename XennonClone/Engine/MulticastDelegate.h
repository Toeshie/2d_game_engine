#pragma once
#include <vector>
#include <memory>

class IDelegateManager {
};

class ISimpleDelegateInvoker : public IDelegateManager {
public:
    virtual void Execute() = 0;
};

template <class TObject>
class SimpleDelegateMember : public ISimpleDelegateInvoker {
public:
    typedef void (TObject::* SimpleDelegateNoParams)();
    SimpleDelegateMember(TObject* target, SimpleDelegateNoParams method) : m_Target(target), m_Method(method){}
    virtual void Execute() override {
        (m_Target->*m_Method)();
    }
    bool Equals(TObject* obj, SimpleDelegateNoParams method) {
        return obj == m_Target && method == m_Method;
    }
private:
    TObject* m_Target;
    SimpleDelegateNoParams m_Method;
};

template <typename ...TArgs>
class IDelegateInvokable : public IDelegateManager {
public:
    virtual void Execute(TArgs... params) = 0;
};

template<class TObject, typename... TArgs>
class DelegateToMember: public IDelegateInvokable<TArgs...> 
{

public:
    typedef void (TObject::* SpecializedDelegateOneParam)(TArgs... params);

    DelegateToMember(TObject* target, SpecializedDelegateOneParam method); //Constructor

    void Execute(TArgs... params) override{
        if (m_target != nullptr) {
            (m_target->*m_Method)(params...); 
        }
    }

    bool Equals(TObject* object, SpecializedDelegateOneParam method) {
        return m_target == object && method == m_Method;
    }

private:
    TObject* m_target;
    SpecializedDelegateOneParam m_Method;
};


template<class TObject, typename... TArgs>
DelegateToMember<TObject, TArgs...>::DelegateToMember(TObject* target, SpecializedDelegateOneParam method) : m_target(target), m_Method(method) {};

template <typename... TArgs>
class MulticastDelegate {
private:

    std::vector<IDelegateInvokable<TArgs...>*> m_Attached;

public:

    ~MulticastDelegate();
    
    template <class T>
    void Add(T* object, void (T::* method)(TArgs... params));

    template <class T>
    void Remove(T* object, void (T::* method)(TArgs... params));

    //Empty all attached functions
    void Clear() {
        for (auto* delegate : m_Attached) {
            delete delegate;
        }
        m_Attached.clear();
    }

    void Broadcast(TArgs ... params) noexcept {
        for (auto* member : m_Attached) {
            if (member != nullptr) {
                member->Execute(params...);
            }
        }
    }
};

template <typename ... TArgs>
MulticastDelegate<TArgs...>::~MulticastDelegate() {
    Clear();
}


template <typename ... TArgs>
template <class T>
void MulticastDelegate<TArgs...>::Add(T* object, void (T::* method)(TArgs... params)) {
    //Throw exception if the object is null
    if (object==nullptr) {
        throw new std::exception;
    }
    IDelegateInvokable<TArgs...>* member = new DelegateToMember<T, TArgs...>(object, method);
    m_Attached.push_back(member);
}
template <typename ... TArgs>
template <class T>
void MulticastDelegate<TArgs...>::Remove(T* object, void (T::* method)(TArgs... params)) {
    for (size_t i = 0; i < m_Attached.size(); ++i) {
        auto* invokable = m_Attached[i];
        if (auto* castedInvokable = dynamic_cast<DelegateToMember<T, TArgs...>*>(invokable)) {
            if (castedInvokable->Equals(object, method)) {
                m_Attached.erase(m_Attached.begin() + i);
                delete invokable;
                break;  // Exit after removing one instance
            }
        }
    }
}

