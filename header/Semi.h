class Semi : protected Connector {
    public:
        Semi ();
        Semi (Base*, Base* );
        ~Semi ();
        bool execute ();
        string getExecutable () {
            return "";
        };
};