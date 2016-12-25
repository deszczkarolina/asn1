#ifndef Exception_h
#define Exception_h

enum except_ids {WRONG_TAG, EMPTY_OBJECT, WRONG_ENUM_VALUE, FILE_NOT_OPEN};

///klasa wyjątków
class Exception
{
    private:
        int id;
    public:
        Exception(int id): id(id) {}
        std::string what()
        {
            switch (id)
            {
                case(WRONG_TAG):
                    return "wrong tag";
                    break;
                case(EMPTY_OBJECT):
                    return "ASNobject is empty ";
                    break;
                case(WRONG_ENUM_VALUE):
                    return "undefined enum value";
                    break;
                case(FILE_NOT_OPEN):
                    return "Couldn't open file";
                    break;
                default:
                    return "Undefined exception";
            }

        }
};

#endif
