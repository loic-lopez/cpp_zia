//
// Created by Eric on 19/02/2018.
//

#ifndef CPP_ZIA_ZIAEXCEPTION_HPP
#define CPP_ZIA_ZIAEXCEPTION_HPP


class ZiaException {
public:
    enum class errors {
        CREATE_SOCKET,
        DELETE_SOCKET,
        CREATE_THREAD,
        DELETE_THREAD,
        BAD_ALLOC,
    };

private:
    errors type;
public:
    ZiaException(errors _type) throw() : type(_type) {}
    ~ZiaException() throw() {}
    virtual const char* what() const throw()
    {
        switch (type) {
            case errors::CREATE_SOCKET : {
                return ("Unable to create a socket");
            }
            case errors::DELETE_SOCKET : {
                return ("Unable to delete a socket");
            }
            case errors::CREATE_THREAD : {
                return ("Unable to create a thread");
            }
            case errors::DELETE_THREAD : {
                return ("Unable to delete a thread");
            }
            case errors::BAD_ALLOC : {
                return ("Unable to create");
            }
        }
        return ("ERROR");
    };
};


#endif //CPP_ZIA_ZIAEXCEPTION_H
