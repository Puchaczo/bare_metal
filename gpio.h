

#define GPIOA_ADR 0x48000000
#define GPIOB_ADR 0x48000400
#define GPIOC_ADR 0x48000800
#define GPIOD_ADR 0x48000C00
#define GPIOE_ADR 0x48001000
#define GPIOF_ADR 0x48001400
#define GPIOG_ADR 0x48001800


typedef struct GPIO_struct
{
	volatile uint32_t MODER_RG;
	volatile uint16_t OTYPER_RG;
	volatile uint16_t RESERVED1;
	volatile uint32_t SPEED_RG;
	volatile uint32_t PUPDR_RG;
	volatile uint16_t IDR_RG;
	volatile uint16_t RESERVED2;
	volatile uint16_t ODR_RG;
	volatile uint16_t RESERVED3;
	volatile uint32_t BSRR_RG;
	volatile uint16_t LCKR_RG;
	volatile uint16_t RESERVED4;
	volatile uint32_t AFRL_RG;
	volatile uint32_t AFRH_RG;
	volatile uint16_t BRR_RG;

}GPIO_struct;


typedef enum
{
	GPIO_0,
	GPIO_1,
	GPIO_2,
	GPIO_3,
	GPIO_4,
	GPIO_5,
	GPIO_6,
	GPIO_7,
	GPIO_8,
	GPIO_9,
	GPIO_10,
	GPIO_11,
	GPIO_12,
	GPIO_13,
	GPIO_14,
	GPIO_15

}GPIO_PINOUT;

typedef enum
{
	INPUT_GPIOMODE,
	OUTPUT_GPIOMODE,
	ALTERNATE_GPIOMODE,
	ANALOG_GPIOMODE
}GPIO_MODER;

typedef enum
{
	LOW_GPIOSPEED,
	MEDIUM_GPIOSPEED,
	HIGH_GPIOSPEED,
	VHIGH_GPIOSPEED
}GPIO_SPEED;

typedef enum
{
	NO_PULL,
	PULLUP,
	PULLDOWN
}GPIO_PULL;

typedef enum
{
	LOW_STATE,
	HIGH_STATE
}GPIO_VAL;


void GPIO_set_mode(uint32_t address,GPIO_PINOUT pin, GPIO_MODER mode)
{
	GPIO_struct* GPIO_pinout = (GPIO_struct*)address;

	BIT_CLR(GPIO_pinout->MODER_RG,pin*2);
	BIT_CLR(GPIO_pinout->MODER_RG,(pin*2)+1);
	BIT_INS(GPIO_pinout->MODER_RG,mode,(pin*2));
}


void GPIO_set_speed(uint32_t address,GPIO_PINOUT pin, GPIO_SPEED speed)
{
	GPIO_struct* GPIO_pinout = (GPIO_struct*)address;

	BIT_CLR(GPIO_pinout->SPEED_RG,pin*2);
	BIT_CLR(GPIO_pinout->SPEED_RG,(pin*2)+1);
	BIT_INS(GPIO_pinout->SPEED_RG,speed,(pin*2));
}


void GPIO_set_pull(uint32_t address,GPIO_PINOUT pin, GPIO_PULL pull)
{
	GPIO_struct* GPIO_pinout = (GPIO_struct*)address;

	BIT_CLR(GPIO_pinout->PUPDR_RG,pin*2);
	BIT_CLR(GPIO_pinout->PUPDR_RG,(pin*2)+1);
	BIT_INS(GPIO_pinout->PUPDR_RG, pull ,(pin*2));
}

void GPIO_reset_val(uint32_t address, GPIO_PINOUT pin)
{
	GPIO_struct* GPIO_pinout = (GPIO_struct*)address;

	BIT_CLR(GPIO_pinout->BSRR_RG,(pin+16));
	BIT_SET(GPIO_pinout->BSRR_RG,(pin+16));
}


void GPIO_set_val(uint32_t address, GPIO_PINOUT pin)
{
	GPIO_struct* GPIO_pinout = (GPIO_struct*)address;

	BIT_CLR(GPIO_pinout->BSRR_RG, pin);
	BIT_SET(GPIO_pinout->BSRR_RG, pin);
}

void led_init(uint32_t address)
{

	//ustawiamy parametry LED (output, low speed, no pullup/down)
	  GPIO_set_mode(GPIOA_ADR,GPIO_5, OUTPUT_GPIOMODE);
	  GPIO_set_speed(GPIOA_ADR,GPIO_5, LOW_GPIOSPEED);
	  GPIO_set_pull(GPIOA_ADR, GPIO_5, NO_PULL);
}

