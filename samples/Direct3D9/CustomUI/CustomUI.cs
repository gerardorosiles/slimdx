﻿/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System.Drawing;
using System.Windows.Forms;
using SampleFramework;
using SlimDX.Direct3D9;

namespace CustomUI
{
    /// <summary>
    /// The top level game object. Manages the entire game.
    /// </summary>
    class CustomUI : Game
    {
        // constants
        const int InitialWidth = 800;
        const int InitialHeight = 600;

        /// <summary>
        /// Gets the Direct3D device.
        /// </summary>
        /// <value>The Direct3D device.</value>
        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        /// <summary>
        /// Gets or sets the clear color.
        /// </summary>
        /// <value>The clear color.</value>
        public Color ClearColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the interface manager.
        /// </summary>
        /// <value>The interface manager.</value>
        public InterfaceManager InterfaceManager
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="CustomUI"/> class.
        /// </summary>
        public CustomUI()
        {
            // initialize the clear color
            ClearColor = Color.FromArgb(0, 45, 50, 170);

            // set up the window
            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Custom UI Sample";
            Window.KeyDown += Window_KeyDown;

            // create the Direct3D device
            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D9, true, InitialWidth, InitialHeight);
        }

        /// <summary>
        /// Handles the KeyDown event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            // F1 toggles between full screen and windowed mode
            // Escape quits the application
            if (e.KeyCode == Keys.F1)
                GraphicsDeviceManager.ToggleFullScreen();
            else if (e.KeyCode == Keys.Escape)
                Exit();
        }

        /// <summary>
        /// Initializes the game.
        /// </summary>
        protected override void Initialize()
        {
            // create the interface manager
            InterfaceManager = new InterfaceManager(Device, Window, "dxutcontrols.dds");
            InterfaceManager.LoadXml("layout.xml");
            InterfaceManager.Initialize(Device);
        }

        /// <summary>
        /// Loads graphical resources.
        /// </summary>
        protected override void LoadContent()
        {
            // allow the interface to load its content
            InterfaceManager.LoadContent();
        }

        /// <summary>
        /// Unloads graphical resources.
        /// </summary>
        protected override void UnloadContent()
        {
            // allow the interface to unload its content
            InterfaceManager.UnloadContent();
        }

        /// <summary>
        /// Releases the game.
        /// </summary>
        protected override void Release()
        {
            // release the interface
            InterfaceManager.Release();
        }

        /// <summary>
        /// Allows the game to perform logic processing.
        /// </summary>
        /// <param name="gameTime">The time passed since the last update.</param>
        protected override void Update(GameTime gameTime)
        {
            // update the interface
            InterfaceManager.Update((float)gameTime.ElapsedGameTime);
        }

        /// <summary>
        /// Called when a frame is ready to be drawn.
        /// </summary>
        /// <param name="gameTime">The time passed since the last frame.</param>
        protected override void Draw(GameTime gameTime)
        {
            // start the scene
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            // draw the interface
            InterfaceManager.Render();

            // end the scene
            Device.EndScene();
        }
    }
}