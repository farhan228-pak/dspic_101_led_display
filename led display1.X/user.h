/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
void ChangeFrequency(void);
void ChangeGain(void);
void FrequencyLED(int k);
void InitApp(void); /* I/O and Peripheral Initialization */
void Burst(void);
void init_ADC(void);
void TogglePower(void);

extern volatile unsigned int pulse_count;
extern volatile int frequency;

//#define LEDf1 LATBbits.LATB3



#define LEDb5 LATBbits.LATB1
//define LEDb6 LATBbits.LATB5
//#define LEDb7 LATBbits.LATB6
//#define LEDb8 LATBbits.LATB7

//#//define Gate_EN1_ON (LATBbits.LATB14=1)
//#define Gate_EN1_OFF (LATBbits.LATB14=0)

//#define Gate_EN2_ON (LATAbits.LATA3=1)
//#define Gate_EN2_OFF (LATAbits.LATA3=0)

/*PTPER Values for diffrent frequency if 30MHz  crystal is used without PLL*/
//
//#define PTPER_170k      1404    //
//#define PTPER_83k       2884    //
//#define PTPER_145k      1647    //
//#define PTPER_100k      2392    // (ACLK*8*period)-8= PTPER  wher as ACLK=30MHz from crystal
//#define PTPER_121k      1976    //
//#define PTPER_77k       3109    //
//#define PTPER_66k       3628    //


/*PTPER Values for diffrent frequency if 8MHz crystal is used with PLL*16*/
#define PER170k      6107    //  169.8KHz
#define PER145k      7118    // 83KHz
#define PER121k      8531    //  145.7KHz
#define PER101k      10231   /* (ACLK*8*period)-8= PTPER  wher as ACLK=30MHz from crystal  */
#define PER83k       12501    //  121.6KHz
#define PER77k       13477    // 77KHz
#define PER66k       15641    //  66.35KHz

/*PTPER Values for diffrent frequency if 8MHz crystal is used with PLL*16*/
#define DUT170k      2035    //  169.8KHz
#define DUT145k      2372    // 83KHz
#define DUT121k      2843    //  145.7KHz
#define DUT101k      3410   /* (ACLK*8*period)-8= PTPER  wher as ACLK=30MHz from crystal  */
#define DUT83k       4167    //  121.6KHz
#define DUT77k       4492    // 77KHz
#define DUT66k       5213    //  66.35KHz






//#define PTPER_101k      10098    //  101.4KHz

//for 100kHz test
//#define PTPER_101k      10030    //  100KHz

/*Burst Value for each frequency*/
#define Burst_pulse_170k      40    //
#define Burst_pulse_145k      40    //
#define Burst_pulse_121k      40    //
#define Burst_pulse_101k      40    /* 40Pulse ON */
#define Burst_pulse_83k       40    //
#define Burst_pulse_77k       40    //
#define Burst_pulse_66k       40

#define Burst_Period_170k      100    //
#define Burst_Period_145k      100    //
#define Burst_Period_121k      100    //
#define Burst_Period_101k      100    /* 100Pulse full period for burst frequency */
#define Burst_Period_83k       100    //
#define Burst_Period_77k       100    //
#define Burst_Period_66k       100    //