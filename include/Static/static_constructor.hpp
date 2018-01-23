//
// Created by loic lopez on 23/01/2018.
//

#ifndef CPP_ZIA_STATIC_CONSTRUCTOR_HPP
#define CPP_ZIA_STATIC_CONSTRUCTOR_HPP

template<void(*ctor)()>
struct static_constructor
{
    struct constructor
    {
        constructor()
        {
            ctor();
        }
    };

    static constructor c;
};

template<void(*ctor)()>
typename static_constructor<ctor>::constructor static_constructor<ctor>::c;

#endif //CPP_ZIA_STATIC_CONSTRUCTOR_HPP
