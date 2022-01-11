//
// task.ino
//
// ---------------------------------------------------------

// History:
// First version: Tue Jan 11 13:36:55 JST 2022 by @hohno_at_kuimc

// ---------------------------------------------------------

boolean task0() {
	return(true);
}




// ---------------------------------------------------------

// taskX - - blinkint LED

// taskX(int arg1, int arg2)
//   arg1 - duration of LED ON (in msec);
//   arg2 - duration of LED OFF (in msec)
// returns
//   true  - LED is ON
//   false - LED is OFF

boolean taskX(int arg1, int arg2) {
	static uint32_t _ten_millis_prev = 0;
	static uint32_t _ten_millis_next = 0;
	static int _prev_arg1 = 0;
	static int _prev_arg2 = 0;
  static boolean _flag = false;

	if ((arg1 == _prev_arg1) && (arg2 == _prev_arg2)) {
		// Bith arg1 and arg2 are not updated
		if (_ten_millis_next <= ten_millis_curr) {
			if (_flag) {
				_flag = false;
				_ten_millis_next += (arg2/10);
				ATT_NOTE_OFF;
			} else {
				_flag = true;
				_ten_millis_next += (arg1/10);;
				ATT_NOTE_ON;
			}
		}
	} else {
		// one of arg1 and arg2 was updated
		_prev_arg1 = arg1;
		_prev_arg2 = arg2;
		_ten_millis_next = (millis() + arg1) / 10;
		_flag = true;
		ATT_NOTE_ON;
	}

	return(_flag);
}

// -------------------------------------

// task1 - - blinkint LED

// task1(int arg1, int arg2)
//   arg1 - duration of LED ON (in msec);
//   arg2 - duration of LED OFF (in msec)
// returns
//   true  - LED is ON
//   false - LED is OFF

boolean task1(int arg1, int arg2) {
	static uint32_t _ten_millis_prev = 0;
	static uint32_t _ten_millis_next = 0;
	static int _prev_arg1 = 0;
	static int _prev_arg2 = 0;
  static boolean _flag = false;

	if ((arg1 == _prev_arg1) && (arg2 == _prev_arg2)) {
		// Bith arg1 and arg2 are not updated
		if (_ten_millis_next <= ten_millis_curr) {
			if (_flag) {
				_flag = false;
				_ten_millis_next += (arg2/10);
				ATT_LED_OFF;
			} else {
				_flag = true;
				_ten_millis_next += (arg1/10);;
				ATT_LED_ON;
			}
		}
	} else {
		// one of arg1 and arg2 was updated
		_prev_arg1 = arg1;
		_prev_arg2 = arg2;
		_ten_millis_next = (millis() + arg1) / 10;
		_flag = true;
		ATT_LED_ON;
	}

	return(_flag);
}

// -------------------------------------

// task3 - RESET Raspberry Pi

// task3(int arg1, boolean arg2)
//    arg1 - duration of pulling down the Reset pin (in msec)
//    arg2 - how many times will it generate Reset pulse (usually it's one)

boolean task3(int32_t arg1, int arg2) {
	static int32_t _prev_arg1 = -1;
	static boolean _flag = false;
	static uint32_t _ten_millis_next = 0;
	static boolean _cnt = 0;

		if (arg2 < 0) {
		_cnt = 0;
		return(true);
	}

	if ((arg1 <= 0) || (arg1 >= 1000*1000L)) {
		return(false);
	}


	if (!_flag) {
		if (_cnt < arg2) {
			_flag = true;
			_cnt++;
	  	_ten_millis_next = (millis() + arg1) / 10;
	  	ATT_RESET_ON;
		}

	} else {
		// flag is true;
		if (_ten_millis_next <= ten_millis_curr) {
			ATT_RESET_OFF;
			_flag = false;
		}
	}
	return(_flag);
}

// ---------------------------------------------------------
