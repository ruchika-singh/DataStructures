class Time{
	public:
		Time();
		Time(int aHour, int aMinute, int aSeconds);

		//accessor methods
		int getHour() const;
		int getMinute() const;
		int getSecond() const;
		//mutator methods
		void setHour(int aHour);
		void setMinute(int aMinute);
		void setSecond(int aSeconds);

		void PrintAMPM();


	private:
		int hour;
		int minute;
		int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);
