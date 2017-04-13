function [BusObject] = CreateBus(busNames, busDataType, busDim)
% This function creates a Simulink Bus object from cell array inputs.
%
%Usage:  [BusObject] = CreateBus(busNames);
%
%Inputs:
% busNames  - Names of bus elements
%
%Outputs:
% BusObject  - Bus Object
%
%Notes:
%

%Version History: Version 1.0
% 04/12/2017  C. Regan     Initial Release (v1.0)
%

%% Check I/O Arguments
% Check the number of inputs
narginchk(1, 3);
if nargin < 3, busDim = [];
    if nargin < 2, busDataType = []; end
end

% Default Values
if isempty(busDataType), busDataType = repmat({'double'}, size(busNames)); end
if isempty(busDim), busDim = repmat({1}, size(busNames)); end

% Check the number of outputs
nargoutchk(0, 1);

%% Create the Bus object

for indxElem = 1:length(busNames)
    % Create BusElement for each field
    busElem(indxElem) = Simulink.BusElement;
    busElem(indxElem).Name = busNames{indxElem};
    busElem(indxElem).Dimensions = busDim{indxElem};
    busElem(indxElem).DataType = busDataType{indxElem};
    busElem(indxElem).SampleTime = -1;
    busElem(indxElem).Complexity = 'real';
    busElem(indxElem).SamplingMode = 'Sample based';
end
BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = busElem;

