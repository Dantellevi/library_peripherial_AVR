	if (count == 1)   //sym 1
		{
		switch (sym)
			{
			case 'R': com_detect = 2; break; //RING
			case 'A': com_detect = 3; break; //ATI
			case 'O': com_detect = 1; break; //OK
			default: com_detect = 0;
			}
		}
	if (count == 2)   //sym 2
		{
	 	switch (sym)
			{
			case 'I': if (com_detect == 2) com_detect = 2; else com_detect = 0; break; //RING
			case 'T': if (com_detect == 3) com_detect = 3; else com_detect = 0; break; //ATI
			case 'K': if (com_detect == 1) com_detect = 1; else com_detect = 0; break; //OK
			default: com_detect = 0;
			}
		}
	if (count == 3)
		{
		switch (sym)
			{
			case 'N': if (com_detect == 2) com_detect = 2; else com_detect = 0; break; //RING
			case 'I': if (com_detect == 3) com_detect = 3; else com_detect = 0; break; //ATI
			default: com_detect = 0;
			}
		}
	if (count == 4)
		{
		switch (sym)
			{
			case 'G': if (com_detect == 2) com_detect = 2; else com_detect = 0; break; //RING
			default: com_detect = 0;
			}
		}
