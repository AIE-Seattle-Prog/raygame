# raygame - sample project

This is a sample C++ project setup with [raylib][raylib] for Visual
Studio 2019. Raylib is a simple game programming framework that is designed to
be friendly to beginners. It is created by [Ramon Santamaria
(@raysan5)][raysan].

This version is compatible with any documentation referring to Raylib 3.0.

It is primarily intended for use by students in the Game Programming course at
the Seattle Campus of the Academy of Interactive Entertainment.

[raylib]:https://github.com/raysan5/raylib
[raysan]:https://github.com/raysan5

## Getting Started

To get started with this sample project, click the _Use this template_ button
up top to copy this repository to your own account. Then, follow the
instructions in the [Building](#building) section below.

Once you've got it working, check out the cheatsheet for more information on
the Raylib API or browse the example projects.

**raylib links** - [website][rl-website] / [discord][rl-discord] / [reddit][rl-reddit] / [raylib repo][rl-repo] / [api reference][rl-cheatsheet], [examples][rl-examples]

[rl-website]:https://www.raylib.com/
[rl-discord]:https://discord.gg/VkzNHUE
[rl-reddit]:https://www.reddit.com/r/raylib/
[rl-repo]:https://github.com/raysan5/raylib/tree/3.0.0
[rl-cheatsheet]:https://www.raylib.com/cheatsheet/cheatsheet.html
[rl-examples]:https://www.raylib.com/examples.html
[rl-examples-repo]:https://github.com/raysan5/raylib/tree/3.0.0/examples
[rl-cs-bindings]:https://github.com/ChrisDill/Raylib-cs
[rl-cs-bindings-ref]:https://github.com/ChrisDill/Raylib-cs/blob/master/Raylib-cs/Raylib.cs
[rl-cs-examples]:https://github.com/ChrisDill/Raylib-cs-Examples

## Building

This project supports by **Visual Studio 2019** or newer.

> **Property**          | **Value**
> ----------------------|--------------------------------
> Windows SDK Version   | 10.0 (latest installed version)
> Platform Toolset      | Visual Studio 2019 (v142)
> C++ Language Standard | ISO C++14 Standard (std:c++14)

When building, please make sure that your installation of Visual Studio has
the necessary components to compile this project, per the table above. If
you get any errors, consult the table above and refer to [Microsoft Docs][msft-modify]
to learn how to configure your installation appropriately.

[msft-modify]:https://docs.microsoft.com/en-us/visualstudio/install/modify-visual-studio?view=vs-2019

Clone the repository and open the solution in Visual Studio. Both the solution
and project should already be configured and ready to start working with. To
test this, build and run the provided sample project.

![A screenshot of the included sample project](.github/raygame.png)

The sample project that is provided is the [basic window example][basicexample]
from raylib. Further examples can be found in its [repository][rl-examples-repo]
or on the [website][rl-examples].

You can review the [cheatsheet][rl-cheatsheet] for the full range of functions made
available through raylib.

[basicexample]:https://github.com/raysan5/raylib/tree/3.0.0/examples/core/core_basic_window.cpp
[rayexamplesite]:https://www.raylib.com/examples.html

## License

MIT License - Copyright (c) 2018-2020 Academy of Interactive Entertainment

For more information, see the [license][lic] file.

Third party works are attributed under [thirdparty.md][3p].

[lic]:license.md
[3p]:thirdparty.md
[raylib]:https://github.com/raysan5/raylib