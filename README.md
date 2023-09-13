# STM32 Telegraph

Write morse code on a 16x2 LCD display using button presses. This project doesn't use GPIO interrupts to make things more challenging.

## Wiring 

## Usage
The lights indicate when an action has been made or cancelled.

- Short presses means dot, blue light quickly turns on and off (100ms).
- Long presses means dash, blue light turns on and off for 500ms.
- If the morse code entered in wrong, the red light blinks for 250ms.
- If more than 3 seconds elapse since the last command, the command stack is cleared and the red light blinks for 250ms.

## Examples

https://github.com/Bloemenstraat/STM32-Telegraph/assets/20916233/051a3285-e3bd-4abc-a4cb-9cfc8786ca7f

https://github.com/Bloemenstraat/STM32-Telegraph/assets/20916233/d03144be-6ac1-4e2b-9279-68fd77b2e77f

