#include "../include/Dependencies.h"

Graph _main(
	MAIN_A,
	{
		MAIN_B,
		C
	},

	{
		{
			MAIN_A,
			State(
				{
					{
						MAIN_A,
						Transition(
							Mark(OPEN),
							{
								"a"
							}
						)
					},

					{
						MAIN_B,
						Transition(
							Mark(CLOSE),
							{
								"b",
								"ccc"
							}
						)
					}
				}
			)
		},

		{
			MAIN_B,
			State(
				{
					{
						MAIN_B,
						Transition(
							Mark(CLOSE),
							{
								"b"
							}
						)
					},

					{
						C,
						Transition(
							Mark(),
							{
								"c"
							}
						)
					}
				}
			)
		},

		{
			C,
			State(
				{
					{
						MAIN_B,
						Transition(
							Mark(),
							{
								"b"
							}
						)
					}
				}
			)
		}
	}
};

Graph _C(
	C_A,
	{
		C_A
	},

	{
		{
			C_A,
			State(
				{
					{
						C_A,
						Transition(
							Mark(),
							{
								"c"
							}
						)
					}
				}
			)
		}
	}
};

std::map<STATE_NAME, Graph> graphs =
	{
		{
			MAIN,
			_main
		},

)		{
			C,
			_C
		}
	};

