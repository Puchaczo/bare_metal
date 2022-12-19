
//makra pomocnicze
#define BIT_SET(byte,n) ((byte) |=  (1<<(n)))
#define BIT_CLR(byte,n) ((byte) &= ~(1<<(n)))
#define BIT_INS(byte,ins,n) ((byte) |= ((ins)<<(n)))

//przerwanie od timera
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)
	{
		TIMER_struct* TIMER_WSK = (TIMER_struct*)TIM2_ADR;
		GPIO_struct* GPIO_WSK = (GPIO_struct*)GPIOA_ADR;

		//toggle led
		GPIO_WSK->ODR_RG ^= (1 << GPIO_5);

		//zerowanie flagi przerwania
		BIT_CLR(TIMER_WSK->SR_RG, 0);
	}

}

int main(void)
{
 
  HAL_Init();
  SystemClock_Config();

  MX_LPUART1_UART_Init();

  //pointer na GPIO w celch wizualizacji zmian, pointer na timer dodatkowo wykorzystywany
  GPIO_struct* gpioa_ptr = (GPIO_struct*)GPIOA_ADR;
  TIMER_struct* timer_ptr = (TIMER_struct*)TIM2_ADR;


  //włączamy taktowanie timera2
  __HAL_RCC_TIM2_CLK_ENABLE();

  //włączamy taktowanie GPIOA
  __HAL_RCC_GPIOA_CLK_ENABLE();

  //dwa sposoby przekazywania adresów:
  //led -> wysyłam sam adres, rzutowanie odbywa się w funkcjach
  //timer -> wysyłam do funkcji zrzutowany wskaźnik
  led_init(GPIOA_ADR);
  timer_init(timer_ptr);


  while (1)
  {

  }

}
