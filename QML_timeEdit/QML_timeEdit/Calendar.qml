import QtQuick 2.6

Rectangle {
    id: calendarArea
    width: 350
    height: 320
    color: "#ecf0f1"
    opacity: 0.8

    property int month
    property int year

    signal selectedDateChanged(date selectedDate)

    Component.onCompleted: {
        var currentDate = new Date()
        setDate(currentDate)
    }

    function setDate(currentDate) {
        dateModel.changeModel(currentDate)
        daysGrid.currentIndex = dateModel.firstDayOffset + currentDate.getDate() - 1
    }


    Item {
        x: 0; y: 0
        width: parent.width
        height: parent.height / 8

        Text {
            id: monthLabel
            anchors.centerIn: parent
            font.family: "Ubuntu"
            font.bold: true
            font.pixelSize: 18
            color: "#2c3e50"
        }

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width / 7
            height: parent.height
            color: "Transparent"

            Text {
                anchors.centerIn: parent
                font.family: "Ubuntu"
                font.bold: true
                font.pixelSize: 18
                color: "#2c3e50"
                text: "<"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    dateModel.showPrevious()
                    daysGrid.currentIndex = -1
                }
            }
        }

        Rectangle {
            anchors.right: parent.right
            anchors.top: parent.top
            width: parent.width / 7
            height: parent.height
            color: "Transparent"

            Text {
                anchors.centerIn: parent
                font.family: "Ubuntu"
                font.bold: true
                font.pixelSize: 18
                color: "#2c3e50"
                text: ">"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    dateModel.showNext()
                    daysGrid.currentIndex = -1
                }
            }
        }
    }

    Item {
        id: monthRow
        x: 0; y: parent.height / 8
        width: parent.width
        height: parent.height / 8

        Row {
            Repeater {
                model: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
                Item {
                    width: calendarArea.width / 7
                    height: calendarArea.height / 8

                    Text {
                        anchors.centerIn: parent
                        font.family: "Ubuntu"
                        font.bold: true
                        font.pixelSize: 18
                        color: "#2c3e50"
                        text: modelData
                    }
                }
            }
        }
    }

    GridView {
        id: daysGrid
        x: 0; y: 2 * parent.height / 8
        width: parent.width
        height:  parent.height * 6 / 8
        cellWidth: parent.width / 7
        cellHeight: parent.height / 8
        interactive: false
        clip: true

        model: dateModel

        delegate: Item {
            id: dayCell
            width: daysGrid.cellWidth
            height: daysGrid.cellHeight

            property bool isOtherMonthDay: model.isOtherMonthDay
            property bool isCurrentDay: model.isCurrentDay
            property bool isSelectedDay: false

            property date dateOfDay: model.dateOfDay

            function color() {
                if (isCurrentDay)
                    return "#1abc9c"            // Current Day Color
                else if (GridView.isCurrentItem)
                    return "#e67e22"            // Seleced Day Color
                else if (isOtherMonthDay)
                    return "#7f8c8d"            // Other Month Day Color
                return "#34495e"                // Day Color
            }

            function bgColor() {
                if (isCurrentDay)
                    return "#e67e22"            // Current Day Color
                else if (GridView.isCurrentItem)
                    return "#1abc9c"            // Seleced Day Color
                else if (isOtherMonthDay)
                    return "Transparent"            // Other Month Day Color
                return "Transparent"                // Day Color
            }

            Rectangle {
                z: 1
                anchors.fill: parent
                radius: 5
                color: dayCell.bgColor()
                opacity: 0.5

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        daysGrid.currentIndex = index
                    }
                }
            }

            Text {
                z: 2
                anchors.centerIn: parent
                font.family: "Ubuntu"
                font.bold: (!isOtherMonthDay) ? true : false
                font.pixelSize: 18
                color: dayCell.color()
                text: dayCell.dateOfDay.getDate()
            }
        }
    }

    ListModel {
        id: dateModel

        signal monthChanged()

        property int firstDayOffset: 0
        property date selectedDate: new Date()
        property date currentDate: new Date()

        function getMonthYearString() {
            return Qt.formatDate(selectedDate, "MMMM yyyy")
        }

        function changeModel(_selectedDate) {
            clear()
            selectedDate = _selectedDate
            fillModel()
            monthChanged()
        }

        function showNext() {
            showOtherMonth(selectedDate.getMonth() + 1)
        }

        function showPrevious() {
            showOtherMonth(selectedDate.getMonth() - 1)
        }

        function fillModel() {
            firstDayOffset = getFirstDayOffset(selectedDate)
            for(var i = 0; i < 6 * 7; ++i) {
                var objectDate = selectedDate;
                objectDate.setDate(selectedDate.getDate() - (selectedDate.getDate() - 1 + firstDayOffset - i))
                appendDayObject(objectDate)
            }
        }

        function appendDayObject(dateOfDay) {
            append({
                       "dateOfDay" : dateOfDay,
                       "isCurrentDay" : dateOfDay.getDate() === currentDate.getDate() &&
                                        dateOfDay.getMonth() === currentDate.getMonth() &&
                                        dateOfDay.getFullYear() === currentDate.getFullYear(),
                       "isOtherMonthDay" : dateOfDay.getMonth() !== selectedDate.getMonth()
                   })
        }

        function showOtherMonth(month) {
            var newDate = selectedDate
            var currentDay = selectedDate.getDate()
            currentDay = getValidDayByMonthAndDay(month, currentDay, isLeapYear(selectedDate.getFullYear()));
            newDate.setMonth(month, currentDay)
            changeModel(newDate)
        }

        function getFirstDayOffset(currentDate) {
            var tmpDate = currentDate
            tmpDate.setDate(currentDate.getDate() - (currentDate.getDate() - 1))
            var firstDayWeekDay = tmpDate.getDay()
            if (firstDayWeekDay === 0)
                firstDayWeekDay = 6
            else
                firstDayWeekDay--
            return firstDayWeekDay
        }

        function getValidDayByMonthAndDay(month, day, leapYear) {
            if (month === 12)
                month = 0
            if (month === -1)
                month = 11

            if (month === 0 ||
                    month === 2 ||
                    month === 4 ||
                    month === 6 ||
                    month === 7 ||
                    month === 9 ||
                    month === 11)
                return day

            if (month !== 1) {
                if (day < 31)
                    return day
                return 30
            }

            if (day < 29)
                return day

            if (leapYear)
                return 29
            return 28
        }

        function isLeapYear(year) {
            if(year % 4 === 0) {
                if(year % 100 === 0) {
                    if(year % 400 === 0) {
                        return true;
                    }
                    else
                        return false;
                }
                else
                    return true;
            }
            return false;
        }

        onMonthChanged: {
            monthLabel.text = getMonthYearString()
            daysGrid.currentIndex = dateModel.firstDayOffset + selectedDate.getDate() - 1
        }

        onSelectedDateChanged: {
            calendarArea.selectedDateChanged(selectedDate)
        }
    }
}

