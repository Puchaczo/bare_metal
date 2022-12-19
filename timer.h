

#define TIM2_ADR 0x40000000
#define TIM3_ADR 0x40000400
#define TIM4_ADR 0x40000800
#define TIM5_ADR 0x40000C00
#define TIM6_ADR 0x40001000
#define TIM7_ADR 0x40001400
#define TIM8_ADR 0x40013400


typedef struct TIMER_struct
{
	volatile uint32_t CR1_RG;
	volatile uint32_t CR2_RG;
	volatile uint32_t SMCR_RG;
	volatile uint32_t DIER_RG;
	volatile uint32_t SR_RG;
	volatile uint32_t EGR_RG;
	volatile uint32_t CCMR1_RG;
	volatile uint32_t CCMR2_RG;
	volatile uint32_t CCER_RG;
	volatile uint32_t CNT_RG;
	volatile uint32_t PSC_RG;
	volatile uint32_t ARR_RG;
	volatile uint32_t RCR_RG;
	volatile uint32_t CCR1_RG;
	volatile uint32_t CCR2_RG;
	volatile uint32_t CCR3_RG;
	volatile uint32_t CCR4_RG;
	volatile uint32_t BDTR_RG;
	volatile uint32_t CCR5_RG;
	volatile uint32_t CCR6_RG;
	volatile uint32_t CCMR3_RG;
	volatile uint32_t DTR2_RG;
	volatile uint32_t ECR_RG;
	volatile uint32_t TISEL_RG;
	volatile uint32_t AF1_RG;
	volatile uint32_t AF2_RG;

}TIMER_struct;


void timer_init(TIMER_struct* timer)
{
	  //wyłączamy timer na czas ustawień
	  BIT_CLR(timer->CR1_RG,0);

	  //stawienia preskalerów
	  timer->PSC_RG = 48000-1;
	  timer->ARR_RG = 1000-1;

	  //update timera w celu zapisania zmian
	  BIT_SET(timer->EGR_RG,0);

	  // włączamy przerwania
	  HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
	  HAL_NVIC_EnableIRQ(TIM2_IRQn);
	  BIT_SET(timer->DIER_RG,0);

	  //włączamy timer
	  BIT_SET(timer->CR1_RG,0);
}
