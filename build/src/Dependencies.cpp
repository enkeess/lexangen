#include "../include/Dependencies.h"

Graph _main(
	MAIN_A,
	{
		MAIN_B
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
								"b"
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
					}
				}
			)
		}
	}
);

std::map<STATE_NAME, Graph> graphs =
	{
		{
			MAIN,
			_main
		}
	};

