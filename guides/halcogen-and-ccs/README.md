# Creating a HALCoGen-Based Project for CCS

## Resources

(How to Create A HALCoGen-Based Project For CCS (Rev. B))[https://www.ti.com/lit/an/spna121b/spna121b.pdf]

## Description

HALCoGen is a code generator that generates code for the Hardware Abstraction Layer (HAL) so you can interface with the board. HALCoGen allows you to configure the board in different ways so different features can be used. By setting up the HALCoGen project inside of the Code Composer Studio (CCS) project, we can change configuration settings in HALCoGen, delete the old HALCoGen code, generate the new code inside of the CCS project, and finally build the project without having to do too much file manipulation.

## Steps

1. Generate a workspace in CCS
2. Create a new project
   - Target: TMS570LS1227
   - Connection: Texas Instruments XDS100v2 USB Debug Probe
   - Give it a name
   - Compiler version doesn't matter(? I used TI 20.2.7.LTS)
   - Project type and tool chain
   - Linker Command file: Leave default (None)
   - Leave the rest default
   - Project template: Empty project. If you generate a main function, you have to disable it before you build, since HALCoGen also generates a main.
   - CCS Project is now set up!
3. Create a HALCoGen Project
   1. File > New > Project
   2. TMS570LS12x -> TMS57-LS1227ZWT
   3. Name: Exact same name as the CCS project
   4. Location: Exact same directory as the CCS project
      - Uncheck "Create directory for project", we're using the CCS directory.
4. Tools: Leave default
5. HALCoGen Project is created!
6. Click Generate Code at the top (Its the one in its own tab, or F5).
7. Register HALCoGen code with CCS
8. Back in the CCS directory, we have new folders, "include" and "source". These are where the HAL files are located.
9. Right click on the project (Bolded top level name in the hierarchy)
10. Properties
11. Build > Arm Compiler > Include Options
12. Add the new include folder to the include search path
    - Probably this: `${workspace_loc:/${ProjName}/include}`
13. Apply and Close

Now, you can build! Use the Hammer icon at the top to compile and link your project.

> [!WARNING]
> Make sure you delete the generated `source` and `include` directories every time you rebuild. If you leave them, they will not be correctly regenerated when you regenerate them inside of HALCoGen.

The main function is in sys_main.c. Note that the function doesn't actually start at main, it starts at `_c_int00` in `sys_startup.c`, which calls main.

The easiest way to run code is to call your own main function from the sys_main.c main. Create a file called hello.c in the root directory, with some function. Here's [mine](my_main.c):

```cpp
# include <stdio.h>

int my_main(void) {
    printf("Hello World!\n");
    return 0;
}
```

Then, in `sys_main`, insert a function declaration after USER CODE BEGIN (2), and call your function after USER CODE BEGIN (3). Here's [mine](sys_main.c):

```cpp
/*USER CODE BEGIN (2) */
int my_main(void);
/* USER CODE END*/

uint8   emacAddress[6U] =   {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
uint32  emacPhyAddress  =   0U;

int main(void){
/*USER CODE BEGIN (3) */
    my_main();
    while(1);
/* USER CODE END*/
    return 0;
}
```

> [!NOTE]
> The while(1) was not there initially. I added that, since, in embedded, the fun never ends!
>
> The main function should never return.

To DEBUG:

1. Connect your hardware board.
2. Add a hardware breakpoint somewhere, by right clicking on a line of code.
3. Press the bug at the top of the screen
4. When the code reaches a hardware breakpoint, it will stop execution.
