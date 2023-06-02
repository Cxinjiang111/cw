class DBConnection{
public:
    static DBConnection create();

    void close();

};
class DBConn{
public:
    void close(){
        db.close();
        closed=true;
    }
    ~DBConn(){
        if(!closed)
        {
            try{
                db.close();
            }
            catch(...)
            {
                //调用失败的情况 结束程序，或吞下异常
            }
        }


    }
private:
    DBConnection db;
    bool closed;
};
/*
一般而言， 将异常吞掉是个坏主意， 因为它压制了 “某些动作失败＂ 的重要 信息！
然而有时候石下异常也比负担 “草率结束程序” 或 “不明确行为带来的风险 “ 好。 
为了让这成为一个可行方案， 程序必须能够继续可靠地执行， 即使在遭 遇并忽略一个错误之后。

个较佳策略是重新设计DBConn接口，使其客户有机会对可能出现的问题作出
反应。例如DBConn自己可以提供一个close函数，因而赋予客户一个机会得以处理
“因该操作而发生的异常”。DBConn也可以追踪其所管理之DBConnection是否已被关闭，
并在答案为否的情况下由其析构函数关闭之。这可防止遗失数据库连接。
 然而如果DBConnection析构函数调用close失败，我们又将退回“强迫结束程序”


把调用close的责任从DBConn析构函数手上移到DBConn客户手上（但DBConn 析构函数仍内含一个 “ 双保险 “ 调用）
可能会给你 ＂ 肆无忌惮转移负担＂ 的印象。 你甚至可能认为它违反条款18所提忠告（让接口容易被正确使用）。
 实际上这两项污名都不成立。 如果某个操作可能在失败时抛出异常， 而又存在某种需要必须处理 该异常，
  那么这个异常必须来自析构函数以外的某个函数。 因为析构函数吐出异常 

就是危险， 总会带来 “过早结束程序” 或“发生不明确行为 ＂ 的风险。 本例要说的
一
是， 由客户自己调用close并不会对他们带来负担， 而是给他们 个处理错误的机
会， 否则他们没机会响应。 如果他们不认为这个机会有用（ 或许他们坚信不会有错 误发生），
可以忽略它，倚赖DBConn析构函数去调用close。如果真有错误发生一一
如果close的确抛出异常——而且DBConn吞下该异常或结束程  
*/