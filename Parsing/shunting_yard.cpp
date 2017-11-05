enum type { op, value, obracket, cbracket }; //types
struct token
{
    string text;
    type ttype;
};

template <typename T>
struct operation
{
    int precedence;
    function<void(stack<T> &s)> operate;
};

void mul(stack<string> &s); //operator
void pluss(stack<string> &s);
void poww(stack<string> &s);

unordered_map<string, operation<string>> operations;

bool rpn(const vector<token> &tokens, queue<token> &rpn)
{
    stack<token> operators;
    for (auto &token : tokens)
    {
        if (token.ttype == value)
            rpn.push(token);
        else if (token.ttype == op)
        {
            while (operators.size() > 0 &&
                   operators.top().ttype != obracket && operations[token.text].precedence > operations[operators.top().text].precedence)
            {
                rpn.push(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
        else if (token.ttype == obracket)
            operators.push(token);
        else if (token.ttype == cbracket)
        {
            while (operators.top().ttype != obracket)
            {
                rpn.push(operators.top());
                operators.pop();
                if (operators.size() == 0)
                    return false;
            }
            operators.pop();
        }
    }
    while (operators.size() > 0)
    {
        if (operators.top().ttype == obracket)
            return false;
        rpn.push(operators.top());
        operators.pop();
    }
    return true;
}

template <typename T>
T eval(queue<token> &rpn, bool &ok)
{
    stack<T> result;
    while (rpn.size() > 0)
    {
        auto t = rpn.front();
        rpn.pop();
        if (t.ttype == value)
            result.push(t.text); //parsear t.text
        if (t.ttype == op)
            operations[t.text].operate(result);
    }
    ok = result.size() == 1;
    return result.top();
}

vector<token> lex(const string &str); //lexer

int main()
{
    operations["*"] = {1, poww};
    operations["."] = {2, mul};
    operations["|"] = {3, pluss};
    string str;
    auto toks = lex(str);
    queue<token> q;
    rpn(toks, q);
    bool ok;
    auto result = eval<string>(q, ok);
    cout << result << '\n';
    return 0;
}