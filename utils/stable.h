#ifndef STABLE_H
#define STABLE_H

#define DEFINE_PROPERTY(type, name)                                      \
                                                                         \
private:                                                                 \
    Q_PROPERTY(type name READ name WRITE set##name NOTIFY name##Changed) \
                                                                         \
private:                                                                 \
    type m_##name;                                                       \
                                                                         \
public:                                                                  \
    void set##name(const type &a)                                        \
    {                                                                    \
        if (a != m_##name) {                                             \
            m_##name = a;                                                \
            emit name##Changed();                                        \
        }                                                                \
    }                                                                    \
                                                                         \
public:                                                                  \
    type name() const                                                    \
    {                                                                    \
        return m_##name;                                                 \
    }                                                                    \
                                                                         \
public:                                                                  \
Q_SIGNALS:                                                               \
    void name##Changed();

#define READONLY_PROPERTY(TYPE, NAME)        \
    Q_PROPERTY(TYPE NAME READ NAME CONSTANT) \
                                             \
public:                                      \
    TYPE NAME() const                        \
    {                                        \
        return m_##NAME;                     \
    }                                        \
                                             \
private:                                     \
    void NAME(TYPE value)                    \
    {                                        \
        m_##NAME = value;                    \
    }                                        \
    TYPE m_##NAME;

#define cfree(_Memory)  \
    if (_Memory) {      \
        delete _Memory; \
        _Memory = NULL; \
    }

template <class T>
class CSingleton {
public:
    static T *Instance()
    {
        static T _instance;  // create static instance of our class
        return &_instance;   // return it
    }

private:
    CSingleton()                   = delete;  // hide constructor
    ~CSingleton()                  = delete;  // hide destructor
    CSingleton(const CSingleton &) = delete;  // hide copy constructor
    CSingleton &operator=(const CSingleton &) = delete;  // hide assign op
};

#endif // ILIVEHELPER_H
