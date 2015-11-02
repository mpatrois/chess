//#include "Dialogs.h"
//
//#ifndef Actions_h
//#define Actions_h
//
//class Chessboard;
//
//class Action
//{
//public:
//    Action () {};
//    virtual void operator()() const=0;
//};
//
//class ActionClose : public Action
//{
//    public:
//
//    ActionClose (bool *backMe):Action()
//    {
//        backMenu=backMe;
//    };
//    virtual void operator()() const
//    {
//        *backMenu=true;
//    };
//
//    private:
//
//    bool *backMenu;
//};
//
//class ActionSave : public Action
//{
//    public:
//    ActionSave (Chessboard **ech);
//
//    virtual void operator()() const;;
//
//    private:
//
//    Chessboard **e;
//};
//
//#endif // !defined Chessboard_h
