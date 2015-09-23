#ifndef WGF_INPUTLISTENER_H
#define WGF_INPUTLISTENER_H

namespace WGF
{
    class InputActionButton;
    class InputActionAxis; //TODO actually create this

    class InputListener
    {
        public:
            /** Default destructor */
            virtual ~InputListener();

            /** \brief called when a button is pressed
            **/
            virtual void ButtonPressed(InputActionButton* button) {}

            /** \brief called when a button is released
            **/
            virtual void ButtonReleased(InputActionButton* button) {}
        protected:
            /** Default constructor - you need to inherit from this class thus it's protected */
            InputListener();
        private:
    };

} // namespace WGF

#endif // WGF_INPUTLISTENER_H
