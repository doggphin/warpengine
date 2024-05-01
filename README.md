Brendan Lancaster
Advanced Computer Graphics
4/30/24

Project contains:
	- Creating a device from a physical device
	- Swap chain, render passes and a graphics pipeline
	- Drawing vertices from a set of index and vertex buffers
	- Shaders with uniform buffers and perspective view
	- Image and texture sampler loading
    - Model loading
	
My project presentation is going to focus on giving a bit more of an in-depth introduction to Vulkan
than the class slides gave rather than on my project (but I'd still like to show this too)
	
To compile and run (assumes you have the Vulkan SDK, VS Code, CMake and vcpkg installed):
- In CMakePresets.json, set configurePresets[environment][VCPKG_ROOT] to your vcpkg root directory
- In src/shaders/compile.sh, modify its paths to point at your current Vulkan version's folder
	- Run src/shaders/compile.sh to generate shader binaries
- Open gameengine.code-workspace and build the project in VS code
	- If VS Code doesn't run the program automatically, run build/Debug/engine.exe

PS: I know there's errors with undestroyed objects, not getting all the required extensions, and my model (I'm pretty sure this has nothing to do with the model loader
and everything to do with Blender exporting my model in a weird way), I'm going to try to sort these out before my presentation

===== EVERYTHING BELOW THIS LINE HAS NOT BEEN EDITED SINCE  4/15/24 : WILL BE UPDATED IN PRESENTATION =====

This is a work-in-progress progress report of my exploration of Vulkan.
So far I've drawn a single triangle, all the work has gone into setting up a graphics device and a pipeline for it.

99% of the code I've written has been from following https://vulkan-tutorial.com.
What I've learned so far (from perspective of me to class- not fully up-to-date with my code):

    - Vulkan is very, very verbose. There's a billion different functions that get progressively longer and longer and as you've heard many times before, it's extremely verbose and you need to be very explicit in everything you do.
        - Hearing it from others didn't really drill this into my head as working with it has.
        - Personally, I think this is a good thing. A lot of aspects of OpenGL just came off as magic to me, and it's nice to get rid of that.

    - Vulkan works through the creation and use of Vulkan-specific objects.
        - These objects are instantiated by specifying values in vk...Info and passing them into a vkCreate... call which returns a Vulkan object
            - These structs are all very similar in structure. 
                - They are primarily differentiated by their (enum) VkStructureType "sType" field which acts as an ID, eg "VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO"
    
    - The structure of a Vulkan application follows the form of:
        - Instance (VkInstance): The (generally) singular root context for a Vulkan application. 
            - If you tried using WebGL, this is basically the "gl" value returned from canvas.getContext("webgl") that's used everywhere

        - Physical device (VkPhysicalDevice): This represents an available GPU, all of which can be discovered through using the vkEnumeratePhysicalDevices() function with a previously created vkInstance.
            - These don't necessarily have to be graphics cards in the traditional sense- for example, along with your graphics card, one of the GPUs discovered could be your CPU's integrated graphics. You'll want to use the one with the best performance, which I've seen done through scoring systems.
            - Different GPUs have different capabilities. For example, if you plan on using compute operations in your program, you need to make sure your vkPhysicalDevice supports them. 
                - You'd check for this by passing it into a "vkGetPhysicalDeviceQueueFamilyProperties()" call, which returns a "VkQueueFamilyProperties" struct, which has a "VkQueueFlags" field, which can be ANDed with the capabilities you're looking for. For the compute operations example, the code would essentially be:
                    - vkQueueFamilyProperties.vkQueueFlags & VkQueueFlagBits.VK_QUEUE_COMPUTE_BIT == 1 ? true : false

        - Logical Device (VkDevice): Created from a vkPhysicalDevice, this is what we'll actually use to interact with the GPU.

        - Swapchain (VkSwapChainKHR- includes "KHR"(Krhonos) as it's an extension, not necessary for offscreen rendering): Holds a buffer of images and views for those images so stuff can actually be displayed to the screen.
            - The "present mode" of the swapchain determines how images are selected to be shown to the screen from its buffer, eg you can instantly draw the most available but get tearing, or store a queue and switch between them

        - Graphics pipeline (VkGraphicsPipeline): Self explanatory
            - Combines the following objects into one giant pipeline:
                - Shader stages, same thing as a shader program in OpenGL
                    - Vulkan reads shaders through bytecode from .spv files, which can be compiled before running a Vulkan application
                        - This is to stop any weird platform-specific interpretations of GLSL from happening
                        - This also means that shader formats other than GLSL can be used as long as it compiles down to bytecode Vulkan can read
                        - Using a VkPipelineDynamicState object allows changing things like drawn line width and blend constants at runtime (optional)
                    - Shader stages can be chosen from what I assume is a list of all compiled shaders
                - Fixed-function state: Includes stuff like rasterizer and blending behaviours
                    - For example, point/line/fill drawing or alpha blending
                    - Also includes stuff like viewports and scissors, which let you do multiple separate displays in one window
                - Pipeline layout: pretty sure this represents in/out uniform value slots
                - Render pass: Essentially the framework framebuffers and multiple passes

        - Command buffer (VkCommandBuffer, also uses VkCommandPool):
            - Used to send commands to the device, eg vkDraw();

    - Go over synchronization techniques