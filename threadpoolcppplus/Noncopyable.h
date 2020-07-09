#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class Noncopyable
{
protected:
        Noncopyable(){}
    ~Noncopyable(){}

    Noncopyable(const Noncopyable&) = delete;
    Noncopyable&operator=(const Noncopyable&) = delete;
};

#endif